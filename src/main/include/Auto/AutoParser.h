#pragma once

#include <frc/Filesystem.h>
#include <wpi/MemoryBuffer.h>
#include <wpi/json.h>
#include <vector>
#include <string>

class AutoParser
{
public:
    static std::vector<std::string> ParseFile(std::string autoName);
};
