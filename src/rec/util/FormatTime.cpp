#include "rec/util/FormatTime.h"

namespace rec {
namespace util {

#if JUCE_MAC

#define PRINT snprintf
#define ARGS 64

#else

#define PRINT _snprintf_s
#define ARGS 64, 64

#endif

String TimeFormat::format(RealTime time) const {
    RealTime secR(floor(time));
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

    bool useHours = displayHours_ == DISPLAY_HOURS or
            (displayHours_ == PERHAPS_DISPLAY_HOURS and hours);

    if (useHours) {
        PRINT(buffer, ARGS, "%02d:%02d%c%02.*f", hours, minutes, ch, decimals_, sf);
    } else {
        minutes += 60 * hours;
        const char* zero = (sec < 10 && decimals_)  ? "0" : "";
        if (leadingZeros_ == LEADING_ZEROS) {
            PRINT(buffer, ARGS, "%02d%c%s%02.*f", minutes, ch, zero, decimals_, sf);
        } else {
            PRINT(buffer, ARGS, "%d%c%s%02.*f", minutes, ch, zero, decimals_, sf);
        }
    }

    return buffer;
}

}  // namespace util
}  // namespace rec
