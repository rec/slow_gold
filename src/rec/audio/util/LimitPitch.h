#pragma once

#include "rec/base/base.h"

namespace rec {
namespace audio {

inline double limitPitch(double semitones) {
    static const auto lowest = -24.0;
    static const auto highest = 24.0;
    return std::min(std::max(semitones, lowest), highest);
}

}  // namespace audio
}  // namespace rec
