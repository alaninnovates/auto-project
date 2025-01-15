#include "Auto/AutoChooser.h"

AutoChooser::AutoChooser()
{
}

void AutoChooser::ShuffleboardInit()
{
    AddChooser();
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
    if (m_autoChoosers.at(m_autoChoosers.size() - 1).positionChooser->GetSelected() != "None")
    {
        AddChooser();
    }
}

void AutoChooser::AddChooser()
{
    std::unique_ptr<frc::SendableChooser<std::string>> posChooser = std::make_unique<frc::SendableChooser<std::string>>();
    posChooser->SetDefaultOption("None", "None");
    for (auto const &pair : AutoConstants::AutoPositionNames)
    {
        posChooser->AddOption(pair.first, pair.first);
    }
    frc::ComplexWidget &posWidget = m_shuffTab.Add("Position" + std::to_string(m_autoChoosers.size() + 1), *posChooser)
                                        .WithWidget(frc::BuiltInWidgets::kComboBoxChooser)
                                        .WithPosition(m_autoChoosers.size(), 0);

    std::unique_ptr<frc::SendableChooser<std::string>> reefChooser = std::make_unique<frc::SendableChooser<std::string>>();
    reefChooser->SetDefaultOption("None", "None");
    for (auto const &pair : AutoConstants::ReefLevelNames)
    {
        reefChooser->AddOption(pair.first, pair.first);
    }
    frc::ComplexWidget &reefWidget = m_shuffTab.Add("ReefLevel" + std::to_string(m_autoChoosers.size() + 1), *reefChooser)
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
