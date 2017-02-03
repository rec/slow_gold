#pragma once

#include "rec/base/base.h"

namespace rec {
namespace audio {
namespace source {

void testSource(PositionableAudioSource* source,
                int numSamples = 32,
                int readOffset = 0,
                int writeOffset = 0);

}  // namespace source
}  // namespace audio
}  // namespace rec

