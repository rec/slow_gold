#pragma once

#include "rec/base/RealTime.h"
#include "rec/base/SampleTime.h"
#include "rec/base/SampleRate.h"
#include "rec/util/range/Range.h"

namespace rec {
namespace audio {

typedef AudioSampleBuffer Buffer;
typedef AudioSourceChannelInfo Info;
typedef PositionableAudioSource Source;

typedef vector<float> LevelVector;

const RealTime MINIMUM_FILE_SIZE = 1.0;

namespace transport {

enum State {STOPPED, RUNNING};
inline State invert(State s) { return s ? STOPPED : RUNNING; }

}  // namespace transport

}  // namespace audio
}  // namespace rec
