#ifndef __REC_AUDIO_SOURCE_GENERICBUFFERSOURCE__
#define __REC_AUDIO_SOURCE_GENERICBUFFERSOURCE__

#include "rec/audio/source/BufferSource.h"

namespace rec {
namespace audio {
namespace source {

class GenericBufferSource : public BufferSource {
 public:
  GenericBufferSource();

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(GenericBufferSource);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_GENERICBUFFERSOURCE__
