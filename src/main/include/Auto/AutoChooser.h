#pragma once
#include <vector>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/shuffleboard/Shuffleboard.h>
#include <iostream>

#include "Auto.h"
#include "AutoParser.h"
#include "Constants/AutoConstants.h"

class AutoChooser
{

public:
    AutoChooser(Auto &autoObj);
    void ShuffleboardInit();
    void ShuffleboardPeriodic();
    void Build();

private:
    void AddChooser(std::string defaultPos = "None", std::string defaultReef = "None");
    bool IsReefPosition(AutoConstants::AutoPosition position);

    struct AutoPathPositionChoosers
    {
        std::unique_ptr<frc::SendableChooser<std::string>> positionChooser;
        frc::ComplexWidget &positionWidget;
        std::unique_ptr<frc::SendableChooser<std::string>> reefChooser;
        frc::ComplexWidget &reefWidget;

        AutoPathPositionChoosers(std::unique_ptr<frc::SendableChooser<std::string>> posChooser, frc::ComplexWidget &posWidget,
                                 std::unique_ptr<frc::SendableChooser<std::string>> reefChooser, frc::ComplexWidget &reefWidget)
            : positionChooser(std::move(posChooser)), positionWidget(posWidget),
              reefChooser(std::move(reefChooser)), reefWidget(reefWidget)
        {
        }
    };

    std::vector<AutoPathPositionChoosers> m_autoChoosers;
    frc::SendableChooser<std::string> m_defaultAutoSetter;
    std::string m_prevDefaultAuto;

    frc::ShuffleboardTab &m_shuffTab = frc::Shuffleboard::GetTab("Auto Chooser");
    nt::GenericEntry *m_previewEntry = m_shuffTab.Add("Preview", "").WithSize(10, 1).WithPosition(0, 3).GetEntry();

    Auto &m_auto;
};
