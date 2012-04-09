#include "rec/util/SystemStats.h"

namespace rec {
namespace util {

SystemStats getSystemStats() {
  typedef juce::SystemStats SS;

  SystemStats ss;
  ss.set_juce_version(str(SS::getJUCEVersion()));
  ss.set_operating_system_type(SS::getOperatingSystemType());
  ss.set_operating_system_name(str(SS::getOperatingSystemName()));

  ss.set_is_operating_system_64_bit(SS::isOperatingSystem64Bit());
#if JUCE_MAC
  ss.set_osx_minor_version_number(SS::getOSXMinorVersionNumber());
#endif
  ss.set_logon_name(str(SS::getLogonName()));
  ss.set_full_user_name(str(SS::getFullUserName()));
  ss.set_computer_name(str(SS::getComputerName()));
  ss.set_num_cpus(SS::getNumCpus());
  ss.set_cpu_speed_in_megahertz(SS::getCpuSpeedInMegaherz());
  ss.set_cpu_vendor(str(SS::getCpuVendor()));
  ss.set_has_mmx(SS::hasMMX());
  ss.set_has_sse(SS::hasSSE());
  ss.set_has_sse2(SS::hasSSE2());
  ss.set_has_3dnow(SS::has3DNow());
  ss.set_memory_size_in_megabytes(SS::getMemorySizeInMegabytes());

  return ss;
}

}  // namespace util
}  // namespace rec
