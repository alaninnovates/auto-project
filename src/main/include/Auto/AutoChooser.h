#include <vector>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/shuffleboard/Shuffleboard.h>

#include "Constants/AutoConstants.h"

class AutoChooser
{
public:
    struct AutoPathPositionChoosers
    {
        std::shared_ptr<frc::SendableChooser<std::string>> positionChooser;
        std::shared_ptr<frc::SendableChooser<std::string>> reefLevelChooser;
        frc::SimpleWidget &positionWidget;
        frc::SimpleWidget &reefLevelWidget;
        AutoPathPositionChoosers(std::shared_ptr<frc::SendableChooser<std::string>> posChooser, frc::SimpleWidget &posWidget, std::shared_ptr<frc::SendableChooser<std::string>> reefChooser, frc::SimpleWidget &reefWidget)
            : positionChooser(posChooser), positionWidget(posWidget), reefLevelChooser(reefChooser), reefLevelWidget(reefWidget) {}
    };
    AutoChooser();
    void ShuffleboardInit();
    void ShuffleboardPeriodic();

private:
    void AddChooser();
    bool IsReefPosition(AutoConstants::AutoPosition position);

    std::vector<AutoPathPositionChoosers> m_autoChoosers;
    frc::ShuffleboardTab &m_shuffTab = frc::Shuffleboard::GetTab("AutoChooser");
};