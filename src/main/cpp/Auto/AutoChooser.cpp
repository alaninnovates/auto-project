#include "Auto/AutoChooser.h"

AutoChooser::AutoChooser() : m_shuff{"AutoChooser"}
{
}

void AutoChooser::ShuffleboardInit()
{
    AddChooser();
    AddChooser();
}

void AutoChooser::ShuffleboardPeriodic()
{
    if (m_autoChoosers.at(m_autoChoosers.size() - 2).GetSelected() != "None")
    {
        AddChooser();
    }
    m_shuff.update(true);
}

void AutoChooser::AddChooser()
{
    frc::SendableChooser<std::string> chooser;
    chooser.SetDefaultOption("None", "None");
    for (auto const &pair : AutoConstants::AutoPositionNames)
    {
        chooser.AddOption(pair.second, pair.second);
    }
    m_autoChoosers.push_back(chooser);
}