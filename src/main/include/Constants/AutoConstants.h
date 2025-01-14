#include <pathplanner/lib/config/RobotConfig.h>

namespace AutoConstants
{
    const pathplanner::RobotConfig ROBOT_CONFIG = pathplanner::RobotConfig::fromGUISettings();
    enum ReefLevel
    {
        L1,
        L2,
        L3,
        L4,
    };

    enum AutoPosition
    {
        NONE,
        START_A,
        START_B,
        START_C,
        PROCESSOR,
        CORAL_MARK_A,
        CORAL_MARK_B,
        CORAL_MARK_C,
        REEF_A,
        REEF_B,
        REEF_C,
        REEF_D,
        REEF_E,
        REEF_F,
        REEF_G,
        REEF_H,
        REEF_I,
        REEF_J,
        REEF_K,
        REEF_L,
    };

    const std::map<AutoPosition, std::string> AutoPositionNames = {
        {NONE, "None"},
        {START_A, "StartA"},
        {START_B, "StartB"},
        {START_C, "StartC"},
        {PROCESSOR, "Processor"},
        {CORAL_MARK_A, "CoralMarkA"},
        {CORAL_MARK_B, "CoralMarkB"},
        {CORAL_MARK_C, "CoralMarkC"},
        {REEF_A, "ReefA"},
        {REEF_B, "ReefB"},
        {REEF_C, "ReefC"},
        {REEF_D, "ReefD"},
        {REEF_E, "ReefE"},
        {REEF_F, "ReefF"},
        {REEF_G, "ReefG"},
        {REEF_H, "ReefH"},
        {REEF_I, "ReefI"},
        {REEF_J, "ReefJ"},
        {REEF_K, "ReefK"},
        {REEF_L, "ReefL"},
    };
}