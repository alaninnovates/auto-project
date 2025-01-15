#pragma once
#include <pathplanner/lib/config/RobotConfig.h>

namespace AutoConstants
{
    const pathplanner::RobotConfig ROBOT_CONFIG = pathplanner::RobotConfig::fromGUISettings();
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
        {"Start A", START_A},
        {"Start B", START_B},
        {"Start C", START_C},
        {"Processor", PROCESSOR},
        {"Coral Mark A", CORAL_MARK_A},
        {"Coral Mark B", CORAL_MARK_B},
        {"Coral Mark C", CORAL_MARK_C},
        {"Reef A", REEF_A},
        {"Reef B", REEF_B},
        {"Reef C", REEF_C},
        {"Reef D", REEF_D},
        {"Reef E", REEF_E},
        {"Reef F", REEF_F},
        {"Reef G", REEF_G},
        {"Reef H", REEF_H},
        {"Reef I", REEF_I},
        {"Reef J", REEF_J},
        {"Reef K", REEF_K},
        {"Reef L", REEF_L},
    };
}