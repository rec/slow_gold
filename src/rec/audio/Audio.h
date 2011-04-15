#ifndef __REC_AUDIO_AUDIO__
#define __REC_AUDIO_AUDIO__

#include "rec/util/Range.h"

namespace rec {
namespace audio {

typedef AudioSampleBuffer Buffer;
typedef AudioSourceChannelInfo Info;
typedef PositionableAudioSource Source;

namespace transport {

enum {STOPPED, RUNNING} State;
State not(State s) { return s ? STOPPED : RUNNING; }

// Bleh, where to put this?
enum Commands {
  TOGGLE_COMMAND, ADD_LOOP_POINT_COMMAND, ZOOM_OUT_COMMAND
};

}  // namespace transport

}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_AUDIO__
