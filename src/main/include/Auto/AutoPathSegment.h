#include <string>
#include <pathplanner/lib/path/PathPlannerPath.h>
#include <pathplanner/lib/trajectory/PathPlannerTrajectory.h>
#include <frc/smartdashboard/SmartDashboard.h>

#include "Constants/AutoConstants.h"

class AutoPathSegment
{
public:
    AutoPathSegment(std::string name);
    pathplanner::PathPlannerTrajectory GetTrajectory();

private:
    std::shared_ptr<pathplanner::PathPlannerPath> m_path;
    pathplanner::PathPlannerTrajectory m_trajectory;
    std::string m_name;
};