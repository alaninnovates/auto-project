#include <vector>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/shuffleboard/Shuffleboard.h>

#include "Constants/AutoConstants.h"

class AutoChooser
{

public:
    AutoChooser();
    void ShuffleboardInit();
    void ShuffleboardPeriodic();

private:
    void AddChooser();
    bool IsReefPosition(AutoConstants::AutoPosition position);

    struct AutoPathPositionChoosers
    {
        frc::SendableChooser<std::string> positionChooser;
        frc::SimpleWidget &positionWidget;
        frc::SendableChooser<std::string> reefChooser;
        frc::SimpleWidget &reefWidget;

        AutoPathPositionChoosers(frc::SendableChooser<std::string> posChooser, frc::SimpleWidget &posWidget,
                                 frc::SendableChooser<std::string> reefChooser, frc::SimpleWidget &reefWidget)
            : positionChooser(std::move(posChooser)), positionWidget(posWidget),
              reefChooser(std::move(reefChooser)), reefWidget(reefWidget)
        {
        }
    };

    std::vector<AutoPathPositionChoosers> m_autoChoosers;
    frc::ShuffleboardTab &m_shuffTab = frc::Shuffleboard::GetTab("Auto Chooser");
};
