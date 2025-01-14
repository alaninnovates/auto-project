#include <cmath>
#include "Util/Utils.h"

#include <frc/smartdashboard/SmartDashboard.h>

class TrapezoidalMotionProfile
{
public:
    struct State
    {
        double position;
        double velocity;
        double acceleration;
    };

    TrapezoidalMotionProfile(double maxVel, double maxAcc);
    State GetState();
    bool AtSetpoint();
    /**
     * Start the profile
     */
    void SetSetpoint(State current, State goal);
    void Periodic();

private:
    bool IsInverted(State current, State goal);
    void CalcPositions(State current, State goal);

    double m_maxVel, m_maxAcc;

    double m_startTime;
    double m_prevTime;

    State m_current;

    double m_endAccel;
    double m_endCoast;
    double m_endDecel;
};
