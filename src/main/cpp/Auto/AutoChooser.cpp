#include "Auto/AutoChooser.h"

AutoChooser::AutoChooser()
{
}

void AutoChooser::ShuffleboardInit()
{
    AddChooser();
    AddChooser();
}

void AutoChooser::ShuffleboardPeriodic()
{
    for (size_t i = 0; i < m_autoChoosers.size(); i++)
    {
        m_autoChoosers.at(i).positionWidget.WithPosition(0, i);
        if (IsReefPosition(AutoConstants::AutoPositionNames.at(m_autoChoosers.at(i).positionChooser->GetSelected())))
        {
            m_autoChoosers.at(i).reefLevelWidget.WithPosition(1, i);
        }
        else
        {
            m_autoChoosers.at(i).reefLevelWidget.WithPosition(-1, i);
        }
    }
    if (m_autoChoosers.size() > 1 && m_autoChoosers.at(m_autoChoosers.size() - 2).positionChooser->GetSelected() != "None")
    {
        AddChooser();
    }
}

void AutoChooser::AddChooser()
{
    auto posChooser = std::make_shared<frc::SendableChooser<std::string>>();
    posChooser->SetDefaultOption("None", "None");
    for (auto const &pair : AutoConstants::AutoPositionNames)
    {
        posChooser->AddOption(pair.first, pair.first);
    }
    auto &posWidget = m_shuffTab.Add("Position" + std::to_string(m_autoChoosers.size() + 1), posChooser.get())
                          .WithWidget(frc::BuiltInWidgets::kComboBoxChooser);
    auto reefChooser = std::make_shared<frc::SendableChooser<std::string>>();
    reefChooser->SetDefaultOption("None", "None");
    for (auto const &pair : AutoConstants::ReefLevelNames)
    {
        reefChooser->AddOption(pair.first, pair.first);
    }
    auto &reefWidget = m_shuffTab.Add("ReefLevel" + std::to_string(m_autoChoosers.size() + 1), reefChooser.get())
                           .WithWidget(frc::BuiltInWidgets::kComboBoxChooser);
    m_autoChoosers.push_back(AutoPathPositionChoosers(posChooser, posWidget, reefChooser, reefWidget));
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
