#pragma once

#include "rec/base/SampleRate.h"
#include "rec/util/Listener.h"

namespace rec {
namespace audio {

// Set the singleton output sample rate for everyone.
SampleRate getOutputSampleRate();
void setOutputSampleRate(SampleRate);

// Use this to subscribe to updates when the output sample rate changes.
Broadcaster<SampleRate>* getOutputSampleRateBroadcaster();

}  // namespace audio
}  // namespace rec
