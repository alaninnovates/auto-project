#include <pathplanner/lib/config/RobotConfig.h>

namespace AutoConstants
{
    const pathplanner::RobotConfig ROBOT_CONFIG = pathplanner::RobotConfig::fromGUISettings();
    enum PathSegment
    {
        CoralMark1_Reef2,
        CoralMark1_Reef3,
        CoralMark2_Reef3,
        CoralMark3_Reef4,
        Home_Reef1,
        Processor_CoralMark1,
        Reef1_Processor,
        Reef2_CoralMark2,
        Reef3_CoralMark2,
        Reef3_CoralMark3,
    };

    const std::map<PathSegment, std::string> PathSegmentNames = {
        {CoralMark1_Reef2, "CoralMark1_Reef2"},
        {CoralMark1_Reef3, "CoralMark1_Reef3"},
        {CoralMark2_Reef3, "CoralMark2_Reef3"},
        {CoralMark3_Reef4, "CoralMark3_Reef4"},
        {Home_Reef1, "Home_Reef1"},
        {Processor_CoralMark1, "Processor_CoralMark1"},
        {Reef1_Processor, "Reef1_Processor"},
        {Reef2_CoralMark2, "Reef2_CoralMark2"},
        {Reef3_CoralMark2, "Reef3_CoralMark2"},
        {Reef3_CoralMark3, "Reef3_CoralMark3"},
    };

    enum AutoAction
    {
        DRIVE,
        SCORE_L1,
        SCORE_L2,
        SCORE_L3,
        SCORE_L4,
        SCORE_PROCESSOR,
        INTAKE_CORAL,
    };

    struct AutoElement
    {
        AutoAction action;
        PathSegment path;
        double offset = 0;
    };

    std::vector<AutoElement> AutoSequence = {
        {DRIVE, Home_Reef1},
        {DRIVE, Reef1_Processor},
        {DRIVE, Processor_CoralMark1},
        {DRIVE, CoralMark1_Reef3},
        {DRIVE, Reef3_CoralMark2},
    };
}