#include "Auto/AutoParser.h"

std::vector<std::string> AutoParser::ParseFile(std::string autoName)
{
    const std::string filePath = frc::filesystem::GetDeployDirectory() + "/pathplanner/autos/" + autoName + ".auto";

    auto fileBuffer = wpi::MemoryBuffer::GetFile(filePath);

    if (!fileBuffer)
    {
        throw std::runtime_error("Cannot open file: " + filePath);
    }

    wpi::json json = wpi::json::parse(fileBuffer.value()->GetCharBuffer());

    auto commandsArr = json.at("command").at("data").at("commands");
    std::vector<std::string> commands;
    for (auto command : commandsArr)
    {
        std::string fullName = command.at("data").at("pathName");
        size_t underscorePos = fullName.find("_");
        if (underscorePos != std::string::npos)
        {
            if (commands.size() == 0)
            {
                commands.emplace_back(fullName.substr(0, underscorePos));
            }
            commands.emplace_back(fullName.substr(underscorePos + 1, fullName.size()));
        }
    }
    return commands;
}