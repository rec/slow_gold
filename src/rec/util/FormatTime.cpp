#include "rec/util/FormatTime.h"

namespace rec {
namespace util {

String TimeFormat::format(RealTime time) const {
  RealTime secR(round(time));
  RealTime fraction(time - secR);
  int sec = static_cast<int>(secR);

  int minutes = sec / 60;
  int hours = minutes / 60;
  sec %= 60;
  double sf = sec + fraction;

  char buffer[64];
  char ch = ':';
  if (flash_ == FLASH && (sec & 1))
    ch = ' ';

#if JUCE_MAC
  if (displayHours_ == DISPLAY_HOURS) {
    snprintf(buffer, 64, "%02d:%02d%c%02.*f", hours, minutes, ch, decimals_, sf);
  } else {
    minutes += 60 * hours;
    const char* zero = (sec < 10 && decimals_)  ? "0" : "";
    if (leadingZeros_ == LEADING_ZEROS) {
      snprintf(buffer, 64, "%02d%c%s%02.*f", minutes, ch, zero, decimals_, sf);
    } else {
      snprintf(buffer, 64, "%d%c%s%02.*f", minutes, ch, zero, decimals_, sf);
    }
  }
#else

  if (displayHours_ == DISPLAY_HOURS) {
    _snprintf_s(buffer, 64, 64, "%02d:%02d%c%02.*f", hours, minutes, ch, decimals_, sf);
  } else {
    minutes += 60 * hours;
    const char* zero = (sec < 10 && decimals_)  ? "0" : "";
    if (leadingZeros_ == LEADING_ZEROS) {
      _snprintf_s(buffer, 64, 64, "%02d%c%s%02.*f", minutes, ch, zero, decimals_, sf);
    } else {
      _snprintf_s(buffer, 64, 64, "%d%c%s%02.*f", minutes, ch, zero, decimals_, sf);
    }
  }
#endif

  return buffer;
}

}  // namespace util
}  // namespace rec
