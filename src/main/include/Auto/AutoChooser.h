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
        std::unique_ptr<frc::SendableChooser<std::string>> positionChooser;
        frc::ComplexWidget &positionWidget;
        std::unique_ptr<frc::SendableChooser<std::string>> reefChooser;
        frc::ComplexWidget &reefWidget;

        AutoPathPositionChoosers(std::unique_ptr<frc::SendableChooser<std::string>> posChooser, frc::ComplexWidget &posWidget,
                                 std::unique_ptr<frc::SendableChooser<std::string>> reefChooser, frc::ComplexWidget &reefWidget)
            : positionChooser(std::move(posChooser)), positionWidget(posWidget),
              reefChooser(std::move(reefChooser)), reefWidget(reefWidget)
        {
        }
    };

    std::vector<AutoPathPositionChoosers> m_autoChoosers;
    frc::ShuffleboardTab &m_shuffTab = frc::Shuffleboard::GetTab("Auto Chooser");
    frc::ShuffleboardTab &m_shuffTabIgnore = frc::Shuffleboard::GetTab("Auto Chooser Ignore");
};
