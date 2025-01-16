#include "Auto/AutoChooser.h"

AutoChooser::AutoChooser(Auto &autoObj) : m_auto{autoObj}
{
}

void AutoChooser::ShuffleboardInit()
{
    for (int i = 0; i < AutoConstants::MAX_AUTO_POSITIONS; i++)
    {
        AddChooser();
    }
    m_defaultAutoSetter = frc::SendableChooser<std::string>();
    m_defaultAutoSetter.SetDefaultOption("None", "None");
    m_defaultAutoSetter.AddOption("Auto", "Auto");
    m_defaultAutoSetter.AddOption("Crazy Auto IDK", "Crazy Auto IDK");
    m_shuffTab.Add("Default Auto Select", m_defaultAutoSetter)
        .WithWidget(frc::BuiltInWidgets::kComboBoxChooser)
        .WithPosition(4, 2)
        .WithSize(2, 1);
    m_defaultAutoSetter.OnChange([this](std::string value)
                                 { Build(); });
}

void AutoChooser::ShuffleboardPeriodic()
{
    // this was a failed idea for a truly dynamic auto chooser... but neither shuffleboard nor elastic supports it properly!!
    // for (size_t i = 0; i < m_autoChoosers.size(); i++)
    // {
    //     m_autoChoosers.at(i).positionWidget.WithPosition(i, 0);
    //     if (IsReefPosition(AutoConstants::AutoPositionNames.at(m_autoChoosers.at(i).positionChooser->GetSelected())))
    //     {
    //         m_autoChoosers.at(i).reefWidget.WithPosition(i, 1);
    //     }
    //     else
    //     {
    //         m_autoChoosers.at(i).reefWidget.WithPosition(i, 100);
    //     }
    // }
    // if (m_autoChoosers.at(m_autoChoosers.size() - 1).positionChooser->GetSelected() != "None")
    // {
    //     AddChooser();
    // }
}

void AutoChooser::AddChooser(std::string defaultPos, std::string defaultReef)
{
    std::unique_ptr<frc::SendableChooser<std::string>> posChooser = std::make_unique<frc::SendableChooser<std::string>>();
    posChooser->SetDefaultOption(defaultPos, defaultPos);
    for (auto const &pair : AutoConstants::AutoPositionNames)
    {
        posChooser->AddOption(pair.first, pair.first);
    }
    frc::ComplexWidget &posWidget = m_shuffTab.Add("Position" + std::to_string(m_autoChoosers.size() + 1), *posChooser)
                                        .WithWidget(frc::BuiltInWidgets::kComboBoxChooser)
                                        .WithPosition(m_autoChoosers.size(), 0);
    posChooser->OnChange([this](std::string value)
                         { Build(); });

    std::unique_ptr<frc::SendableChooser<std::string>> reefChooser = std::make_unique<frc::SendableChooser<std::string>>();
    reefChooser->SetDefaultOption(defaultReef, defaultReef);
    for (auto const &pair : AutoConstants::ReefLevelNames)
    {
        reefChooser->AddOption(pair.first, pair.first);
    }
    frc::ComplexWidget &reefWidget = m_shuffTab.Add("Reef" + std::to_string(m_autoChoosers.size() + 1) + "Level", *reefChooser)
                                         .WithWidget(frc::BuiltInWidgets::kComboBoxChooser)
                                         .WithPosition(m_autoChoosers.size(), 1);

    m_autoChoosers.emplace_back(AutoPathPositionChoosers(std::move(posChooser), posWidget, std::move(reefChooser), reefWidget));
}

bool AutoChooser::IsReefPosition(AutoConstants::AutoPosition position)
{
    return position == AutoConstants::AutoPosition::REEF_A ||
           position == AutoConstants::AutoPosition::REEF_B ||
           position == AutoConstants::AutoPosition::REEF_C ||
           position == AutoConstants::AutoPosition::REEF_D ||
           position == AutoConstants::AutoPosition::REEF_E ||
           position == AutoConstants::AutoPosition::REEF_F ||
           position == AutoConstants::AutoPosition::REEF_G ||
           position == AutoConstants::AutoPosition::REEF_H ||
           position == AutoConstants::AutoPosition::REEF_I ||
           position == AutoConstants::AutoPosition::REEF_J ||
           position == AutoConstants::AutoPosition::REEF_K ||
           position == AutoConstants::AutoPosition::REEF_L;
}

void AutoChooser::Build()
{
    m_auto.ClearSegments();
    std::string previewStr = "";
    if (m_defaultAutoSetter.GetSelected() != "None")
    {
        std::vector<std::string> pathNames = AutoParser::ParseFile(m_defaultAutoSetter.GetSelected());
        for (size_t i = 0; i < pathNames.size() - 1; i++)
        {
            std::string leftPosChooser = m_autoChoosers.at(i).positionChooser->GetSelected();
            std::string rightPosChooser = m_autoChoosers.at(i + 1).positionChooser->GetSelected();
            std::string leftPos = leftPosChooser == "None" ? pathNames.at(i) : leftPosChooser;
            std::string rightPos = rightPosChooser == "None" ? pathNames.at(i + 1) : rightPosChooser;
            previewStr += "(" + std::to_string(i + 1) + ") " + leftPos + " -> ";
            if (i == pathNames.size() - 2)
            {
                previewStr += "(" + std::to_string(i + 2) + ") " + rightPos;
            }
            m_auto.AddSegment(leftPos, rightPos);
        }
    }
    else
    {
        for (size_t i = 0; i < m_autoChoosers.size() - 1; i++)
        {
            std::string pos = m_autoChoosers.at(i).positionChooser->GetSelected();
            std::string nextPos = m_autoChoosers.at(i + 1).positionChooser->GetSelected();
            if (nextPos == "None")
            {
                previewStr += "(" + std::to_string(i + 1) + ") " + pos;
                break;
            }
            previewStr += "(" + std::to_string(i + 1) + ") " + pos + " -> ";
            m_auto.AddSegment(pos, nextPos);
        }
    }
    m_previewEntry->SetString(previewStr);
}