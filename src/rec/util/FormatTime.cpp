#include "rec/util/FormatTime.h"

namespace rec {
namespace util {

#ifdef _WIN32
#define snprintf _snprintf
#endif

const String formatTime(double time, bool flash, bool displayMs, bool displayHours) {
  int sec = static_cast<int>(time);
  double fraction = time - sec;
  int ms = static_cast<int>(1000 * fraction);

  int minutes = sec / 60;
  int hours = minutes / 60;
  sec %= 60;

  char buffer[64];
  char ch = ':';
  if (flash && (sec & 1))
    ch = ' ';

  if (displayHours) {
    if (displayMs)
      snprintf(buffer, 64, "%02d:%02d%c%02d.%03d", hours, minutes, ch, sec, ms);
    else
      snprintf(buffer, 64, "%02d:%02d%c%02d", hours, minutes, ch, sec);
  } else {
    minutes += 60 * hours;
    if (displayMs)
      snprintf(buffer, 64, "%03d%c%02d.%03d", minutes, ch, sec, ms);
    else
      snprintf(buffer, 64, "%03d%c%02d", minutes, ch, sec);
  }

  return buffer;
}

}  // namespace util
}  // namespace rec
