// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <wpi/print.h>

Robot::Robot() : m_auto{}, m_autoChooser{} {}

void Robot::RobotPeriodic()
{
  frc::SmartDashboard::PutNumber("Timer", m_timer.Get().to<double>());
}

void Robot::AutonomousInit()
{
  m_timer.Start();
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
