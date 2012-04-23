#ifndef __REC_AUDIO_UTIL_FILLABLE_FRAME_BUFFER__
#define __REC_AUDIO_UTIL_FILLABLE_FRAME_BUFFER__

#include "rec/audio/util/BufferedReader.h"

namespace rec {
namespace audio {
namespace util {

// Skin
const static int FILLABLE_FRAME_BLOCK_SIZE = 10240;

template <typename Sample, int CHANNELS>
BufferedReader* makeBufferedReader(int size = FILLABLE_FRAME_BLOCK_SIZE);

}  // namespace util
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_UTIL_FILLABLE_FRAME_BUFFER__
