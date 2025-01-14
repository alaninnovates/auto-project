#include "Util/PID.h"

#include <iostream>
#include "Util/Utils.h"

PID::PID(double kp, double ki, double kd, double tol)
    : m_kp(kp), m_ki(ki), m_kd(kd), m_tol(tol)
{
    Reset();
}

double PID::Calculate(double curr_pos)
{
    double t = Utils::GetCurTimeS();
    double dt = t - m_prevT;

    double error = m_setpoint - curr_pos;
    frc::SmartDashboard::PutNumber("PID Error", error);
    m_accum += error * dt;

    m_prevError = error;
    m_prevT = t;

    return m_kp * error + m_ki * m_accum + m_kd * (error - m_prevError) / dt;
}

void PID::Reset()
{
    m_accum = 0.0;
    m_prevError = 0.0;
    m_prevT = Utils::GetCurTimeS();
}

bool PID::AtTarget()
{
    return std::abs(m_error) < m_tol;
}

void PID::SetPID(double kp, double ki, double kd)
{
    m_kp = kp;
    m_ki = ki;
    m_kd = kd;
}

void PID::SetSetpoint(double setpoint)
{
    m_setpoint = setpoint;
}
