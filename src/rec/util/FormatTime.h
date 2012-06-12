#ifndef __REC_UTIL_FORMATTIME__
#define __REC_UTIL_FORMATTIME__

#include "rec/base/SampleTime.h"
#include "rec/util/Math.h"

namespace rec {
namespace util {

inline const String formatTime(SampleTime time,
                               SampleTime mTime,
                               bool flash = false,
                               bool leadingZeros = true,
                               int decimals = 3) {
  SampleTime maxTime = std::max(time, mTime);
  int sampleRate = static_cast<int>(SampleTime::getSampleRate());

  bool displayHours = (maxTime >= 3600 * sampleRate);

  int frac = static_cast<int>(mod(time.get(), sampleRate));
  int sec = static_cast<int>((time - frac).toRealTime());
  double fraction = frac / (1.0 * sampleRate);

  int minutes = sec / 60;
  int hours = minutes / 60;
  sec %= 60;
  double sf = sec + fraction;

  char buffer[64];
  char ch = ':';
  if (flash && (sec & 1))
    ch = ' ';

#if JUCE_MAC
  if (displayHours) {
    snprintf(buffer, 64, "%02d:%02d%c%02.*f", hours, minutes, ch, decimals, sf);
  } else {
    minutes += 60 * hours;
    const char* zero = (sec < 10 && decimals)  ? "0" : "";
    if (leadingZeros) {
      snprintf(buffer, 64, "%02d%c%s%02.*f", minutes, ch, zero, decimals, sf);
    } else {
      snprintf(buffer, 64, "%d%c%s%02.*f", minutes, ch, zero, decimals, sf);
    }
  }
#else

  if (displayHours) {
    _snprintf_s(buffer, 64, 64, "%02d:%02d%c%02.*f", hours, minutes, ch, decimals, sf);
  } else {
    minutes += 60 * hours;
    const char* zero = (sec < 10 && decimals)  ? "0" : "";
    if (leadingZeros) {
      _snprintf_s(buffer, 64, 64, "%02d%c%s%02.*f", minutes, ch, zero, decimals, sf);
    } else {
      _snprintf_s(buffer, 64, 64, "%d%c%s%02.*f", minutes, ch, zero, decimals, sf);
    }
  }
#endif

  return buffer;
}

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_FORMATTIME__
