#include "rec/util/FormatTime.h"

namespace rec {
namespace util {

#ifdef _WIN32
#define snprintf _snprintf
#endif

const String formatTime(RealTime time, bool flash, bool displayHours, bool leadingZeros, int decimals) {
  int sec = static_cast<int>(time.time_);
  double fraction = time - sec * 1.0;

  int minutes = sec / 60;
  int hours = minutes / 60;
  sec %= 60;
  double sf = sec + fraction;

  char buffer[64];
  char ch = ':';
  if (flash && (sec & 1))
    ch = ' ';

  if (displayHours) {
    snprintf(buffer, 64, "%02d:%02d%c%02.*f", hours, minutes, ch, decimals, sf);
  } else {
    minutes += 60 * hours;
    const char* zero = (sec < 10 && decimals)  ? "0" : "";
    if (leadingZeros) {
      snprintf(buffer, 64, "%03d%c%s%02.*f", minutes, ch, zero, decimals, sf);
    } else {
      snprintf(buffer, 64, "%d%c%s%02.*f", minutes, ch, zero, decimals, sf);
    }
  }

  return buffer;
}

}  // namespace util
}  // namespace rec
