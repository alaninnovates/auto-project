#include "Util/TrapezoidalMotionProfile.h"

TrapezoidalMotionProfile::TrapezoidalMotionProfile(double maxVel, double maxAcc) : m_maxVel{std::abs(maxVel)}, m_maxAcc{std::abs(maxAcc)}, m_startTime{-1} {}

void TrapezoidalMotionProfile::SetSetpoint(State current, State goal)
{
    if (m_startTime == -1)
    {
        m_startTime = Utils::GetCurTimeS();
    }
    CalcPositions(current, goal);
}

void TrapezoidalMotionProfile::CalcPositions(State current, State goal)
{
    m_current = current;
    goal = goal;
    if (m_current.velocity > m_maxAcc)
    {
        m_current.velocity = m_maxAcc;
    }

    // Deal with a possibly truncated motion profile (with nonzero initial or
    // final velocity) by calculating the parameters as if the profile began and
    // ended at zero velocity
    double cutoffBegin = m_current.velocity / m_maxAcc;
    double cutoffDistBegin = cutoffBegin * cutoffBegin * m_maxAcc / 2.0;

    double cutoffEnd = goal.velocity / m_maxAcc;
    double cutoffDistEnd = cutoffEnd * cutoffEnd * m_maxAcc / 2.0;

    // Now we can calculate the parameters as if it was a full trapezoid instead
    // of a truncated one

    double fullTrapezoidDist = cutoffDistBegin + (goal.position - m_current.position) + cutoffDistEnd;
    double accelerationTime = m_maxVel / m_maxAcc;

    double fullSpeedDist = fullTrapezoidDist - accelerationTime * accelerationTime * m_maxAcc;

    // Handle the case where the profile never reaches full speed
    if (fullSpeedDist < 0)
    {
        accelerationTime = sqrt(fullTrapezoidDist / m_maxAcc);
        fullSpeedDist = 0;
    }

    m_endAccel = accelerationTime - cutoffBegin;
    m_endCoast = m_endAccel + fullSpeedDist / m_maxVel;
    m_endDecel = m_endCoast + accelerationTime - cutoffEnd;
}

void TrapezoidalMotionProfile::Periodic()
{
    if (m_startTime == -1)
    {
        return;
    }

    double curTime = Utils::GetCurTimeS() - m_startTime;
    double dt = curTime - m_prevTime;
    m_prevTime = curTime;

    if (curTime < m_endAccel)
    {
        m_current.position += m_current.velocity * dt + 0.5 * m_maxAcc * dt * dt;
        m_current.velocity += m_maxAcc * dt;
        m_current.acceleration = m_maxAcc;
    }
    else if (curTime < m_endCoast)
    {
        m_current.position += m_current.velocity * dt;
        m_current.velocity = m_maxVel;
        m_current.acceleration = 0;
    }
    else if (curTime < m_endDecel)
    {
        m_current.position += m_current.velocity * dt - 0.5 * m_maxAcc * dt * dt;
        m_current.velocity -= m_maxAcc * dt;
        m_current.acceleration = -m_maxAcc;
    }
    else
    {
        m_current.position += m_current.velocity * dt;
        m_current.velocity = 0;
        m_current.acceleration = 0;
        m_startTime = -1;
    }
}

bool TrapezoidalMotionProfile::AtSetpoint()
{
    return m_startTime == -1;
}

TrapezoidalMotionProfile::State TrapezoidalMotionProfile::GetState()
{
    return m_current;
}

bool TrapezoidalMotionProfile::IsInverted(State current, State goal)
{
    return goal.position < current.position;
}