// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <frc/smartdashboard/SmartDashboard.h>

Robot::Robot() : m_auto{}, m_autoChooser{m_auto} {}

void Robot::RobotPeriodic()
{
}

void Robot::AutonomousInit()
{
  // todo: don't do this it takes a long time to build. just directly start building in autochooser.
  m_autoChooser.Build();
  m_auto.AutoStart();
}

void Robot::AutonomousPeriodic()
{
  m_auto.Periodic();
}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {}

void Robot::DisabledInit()
{
  m_autoChooser.ShuffleboardInit();
}

void Robot::DisabledPeriodic()
{
  m_autoChooser.ShuffleboardPeriodic();
}

void Robot::TestInit() {}

void Robot::TestPeriodic() {}

void Robot::SimulationInit() {}

void Robot::SimulationPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main()
{
  return frc::StartRobot<Robot>();
}
#endif
