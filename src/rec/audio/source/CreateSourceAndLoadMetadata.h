#ifndef __REC_AUDIO_SOURCE_CREATESOURCEANDLOADMETADATA__
#define __REC_AUDIO_SOURCE_CREATESOURCEANDLOADMETADATA__

#include "rec/base/base.h"

namespace rec {
namespace audio {
namespace source {

PositionableAudioSource* createSourceAndLoadMetadata(const VirtualFile& file);

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_CREATESOURCEANDLOADMETADATA__
