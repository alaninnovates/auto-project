#include <frc/smartdashboard/SmartDashboard.h>

class PID
{
public:
    PID(double kp, double ki, double kd, double tol);
    double Calculate(double curr_pos);
    void SetPID(double kp, double ki, double kd);
    void SetSetpoint(double setpoint);
    void Reset();
    bool AtTarget();

private:
    double m_kp, m_ki, m_kd;
    double m_tol;

    double m_setpoint;
    double m_error;
    double m_accum;
    double m_prevError;
    double m_prevT;
};