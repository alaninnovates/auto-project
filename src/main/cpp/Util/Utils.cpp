#include "Util/Utils.h"

std::size_t Utils::GetCurTimeMs()
{
  auto curTime = frc::Timer::GetFPGATimestamp();
  auto timeMs = curTime.convert<units::millisecond>();
  return static_cast<std::size_t>(timeMs.value());
}

double Utils::GetCurTimeS()
{
  auto curTime = frc::Timer::GetFPGATimestamp();
  auto timeS = curTime.convert<units::second>();
  return timeS.value();
}
