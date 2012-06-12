#ifndef __REC_AUDIO_SAMPLERATE__
#define __REC_AUDIO_SAMPLERATE__

#include "rec/util/Listener.h"

namespace rec {
namespace audio {

int getSampleRate();
void setSampleRate(int);

Broadcaster<int>* getSampleRateBroadcaster();


}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SAMPLERATE__
