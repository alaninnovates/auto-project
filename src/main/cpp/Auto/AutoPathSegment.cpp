#include "Auto/AutoPathSegment.h"

AutoPathSegment::AutoPathSegment(std::string name) : m_name(name)
{
    m_path = pathplanner::PathPlannerPath::fromPathFile(name);
    auto idealTraj = m_path.get()->getIdealTrajectory(AutoConstants::ROBOT_CONFIG);
    if (idealTraj.has_value())
    {
        m_trajectory = idealTraj.value();
    }
    else
    {
        frc::SmartDashboard::PutString(name + "Error", "Failed to generate trajectory for path " + name);
    }
}

pathplanner::PathPlannerTrajectory AutoPathSegment::GetTrajectory()
{
    return m_trajectory;
}