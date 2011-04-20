#ifndef __REC_AUDIO_AUDIO__
#define __REC_AUDIO_AUDIO__

#include "rec/util/Range.h"

namespace rec {
namespace audio {

typedef AudioSampleBuffer Buffer;
typedef AudioSourceChannelInfo Info;
typedef PositionableAudioSource Source;

namespace transport {

enum State {STOPPED, RUNNING};
State invert(State s) { return s ? STOPPED : RUNNING; }

}  // namespace transport

}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_AUDIO__
