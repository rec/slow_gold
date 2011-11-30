#ifndef __REC_UTIL_FORMATTIME__
#define __REC_UTIL_FORMATTIME__

#include "rec/base/Samples.h"
#include "rec/util/Math.h"

namespace rec {
namespace util {

template <int RATE>
const String formatTime(Samples<RATE> time,
                        Samples<RATE> mTime,
                        bool flash = false,
                        bool leadingZeros = true,
                        int decimals = 3) {
  Samples<RATE> maxTime = std::max(time, mTime);
  bool displayHours = (maxTime >= 3600 * RATE);

  int frac = static_cast<int>(mod(time.get(), RATE));
  int sec = static_cast<int>((time - frac).toRealTime());
  double fraction = frac / (1.0 * RATE);

  int minutes = sec / 60;
  int hours = minutes / 60;
  sec %= 60;
  double sf = sec + fraction;

  char buffer[64];
  char ch = ':';
  if (flash && (sec & 1))
    ch = ' ';

  if (displayHours) {
#ifdef _WIN32
    _snprintf(
#else
    snprintf(
#endif
      buffer, 64, "%02d:%02d%c%02.*f", hours, minutes, ch, decimals, sf);
  } else {
    minutes += 60 * hours;
    const char* zero = (sec < 10 && decimals)  ? "0" : "";
    if (leadingZeros) {
      snprintf(buffer, 64, "%02d%c%s%02.*f", minutes, ch, zero, decimals, sf);
    } else {
      snprintf(buffer, 64, "%d%c%s%02.*f", minutes, ch, zero, decimals, sf);
    }
  }

  return buffer;
}

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_FORMATTIME__
