#pragma once

#include "rec/base/SampleRate.h"
#include "rec/audio/stretch/Stretch.pb.h"

namespace rec {
namespace audio {
namespace stretch {

double timeScale(const StretchParameters&);
double pitchScale(const StretchParameters&);
double pitchSemitones(const StretchParameters&);

}  // namespace stretch
}  // namespace audio
}  // namespace rec

