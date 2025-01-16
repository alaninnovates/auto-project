#include "Auto/Auto.h"

Auto::Auto()
{
}

void Auto::AutoStart()
{
    m_autoStart = Utils::GetCurTimeMs();
    m_curPathIndex = 0;
    m_curPathStartTime = m_autoStart;
    m_curTrajectory = m_paths[m_curPathIndex]->GetTrajectory();
}

void Auto::Periodic()
{
    double curTime = Utils::GetCurTimeMs();
    if (m_curPathIndex < m_paths.size())
    {
        frc::SmartDashboard::PutNumber("Cur Time", curTime);
        // frc::SmartDashboard::PutNumber("Cur Time Relative", curTime - m_curPathStartTime);
        auto t = units::second_t{(curTime - m_curPathStartTime) / 1000};
        frc::SmartDashboard::PutNumber("Cur Time Relative", t.to<double>());
        auto state = m_curTrajectory.sample(t);
        publisher.Set(state.pose);
        if (curTime - m_curPathStartTime > m_curTrajectory.getTotalTime().to<double>() * 1000 && m_curPathIndex < m_paths.size() - 1)
        {
            m_curPathIndex++;
            m_curPathStartTime = curTime;
            m_curTrajectory = m_paths[m_curPathIndex]->GetTrajectory();
        }
    }
}

void Auto::ShuffleboardInit() {}

void Auto::ShuffleboardPeriodic() {}

void Auto::SimulationPeriodic() {}

void Auto::AddSegment(std::string position1, std::string position2)
{
    m_paths.push_back(new AutoPathSegment(position1 + "_" + position2));
};

void Auto::ClearSegments()
{
    for (size_t i = 0; i < m_paths.size(); i++)
    {
        delete m_paths.at(i);
    }
    m_paths.clear();
}