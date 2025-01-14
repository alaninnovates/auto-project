#include <vector>
#include <string>

#include <networktables/NetworkTableInstance.h>
#include <networktables/StructTopic.h>
#include <pathplanner/lib/trajectory/PathPlannerTrajectoryState.h>
#include <frc/smartdashboard/SmartDashboard.h>

#include "Util/Utils.h"
#include "AutoPathSegment.h"

class Auto
{
public:
    Auto();
    void AutoStart();
    void Periodic();
    void ShuffleboardInit();
    void ShuffleboardPeriodic();
    void SimulationPeriodic();

private:
    std::vector<AutoPathSegment *> m_paths;
    std::vector<std::string> m_pathNames = {"Home_Reef1", "Reef1_Processor", "Processor_CoralMark1", "CoralMark1_Reef3", "Reef3_CoralMark2"};
    int m_curPathIndex;
    pathplanner::PathPlannerTrajectory m_curTrajectory;
    double m_autoStart;
    double m_curPathStartTime;
    nt::StructPublisher<frc::Pose2d>
        publisher = nt::NetworkTableInstance::GetDefault()
                        .GetStructTopic<frc::Pose2d>("RobotPose")
                        .Publish();
};