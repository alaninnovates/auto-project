#pragma once
#include <pathplanner/lib/config/RobotConfig.h>

namespace AutoConstants
{
    const pathplanner::RobotConfig ROBOT_CONFIG = pathplanner::RobotConfig::fromGUISettings();
    const int MAX_AUTO_POSITIONS = 10;

    enum ReefLevel
    {
        LNONE,
        L1,
        L2,
        L3,
        L4,
    };

    const std::map<std::string, ReefLevel> ReefLevelNames = {
        {"None", LNONE},
        {"L1", L1},
        {"L2", L2},
        {"L3", L3},
        {"L4", L4},
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

    const std::map<std::string, AutoPosition> AutoPositionNames = {
        {"None", NONE},
        {"StartA", START_A},
        {"StartB", START_B},
        {"StartC", START_C},
        {"Processor", PROCESSOR},
        {"CoralMarkA", CORAL_MARK_A},
        {"CoralMarkB", CORAL_MARK_B},
        {"CoralMarkC", CORAL_MARK_C},
        {"ReefA", REEF_A},
        {"ReefB", REEF_B},
        {"ReefC", REEF_C},
        {"ReefD", REEF_D},
        {"ReefE", REEF_E},
        {"ReefF", REEF_F},
        {"ReefG", REEF_G},
        {"ReefH", REEF_H},
        {"ReefI", REEF_I},
        {"ReefJ", REEF_J},
        {"ReefK", REEF_K},
        {"ReefL", REEF_L},
    };
}