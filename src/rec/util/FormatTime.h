#pragma once

#include "rec/base/SampleRate.h"
#include "rec/base/SampleTime.h"
#include "rec/util/Math.h"

namespace rec {
namespace util {

struct TimeFormat {
    enum Flash { NO_FLASH, FLASH };
    enum LeadingZeros { NO_LEADING_ZEROS, LEADING_ZEROS };
    enum DisplayHours { NO_DISPLAY_HOURS, DISPLAY_HOURS, PERHAPS_DISPLAY_HOURS };

    Flash flash_;
    LeadingZeros leadingZeros_;
    int decimals_;
    DisplayHours displayHours_;

    void setDisplayHours(RealTime maxTime) {
    }

    TimeFormat(Flash flash = NO_FLASH, LeadingZeros leadingZeros = LEADING_ZEROS,
                          int decimals = 3, DisplayHours displayHours = PERHAPS_DISPLAY_HOURS)
            : flash_(flash),
                leadingZeros_(leadingZeros),
                decimals_(decimals),
                displayHours_(displayHours) {
    }

    String format(RealTime) const;

    String format(RealTime time, RealTime maxTime) {
        bool hours = (std::max(time, maxTime) >= 3600.0);
        displayHours_ = hours ? DISPLAY_HOURS : NO_DISPLAY_HOURS;
        return format(time);
    }

    String format(SampleTime time, SampleTime maxTime, SampleRate rate) {
        return format(RealTime(time, rate), RealTime(maxTime, rate));
    }
};


}  // namespace util
}  // namespace rec

