#include <vector>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/smartdashboard/SmartDashboard.h>

#include "ShuffleboardSender/ShuffleboardSender.h"
#include "Constants/AutoConstants.h"

class AutoChooser
{
public:
    AutoChooser();
    void ShuffleboardInit();
    void ShuffleboardPeriodic();

private:
    void AddChooser();

    ShuffleboardSender m_shuff;
    std::vector<frc::SendableChooser<std::string>> m_autoChoosers;
};