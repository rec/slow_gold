#ifndef __REC_AUDIO_SOURCE_VIRTUALFILESOURCE__
#define __REC_AUDIO_SOURCE_VIRTUALFILESOURCE__

#include "rec/base/base.h"

namespace rec {
namespace audio {
namespace source {

PositionableAudioSource* virtualFileSource(const VirtualFile& file);

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_VIRTUALFILESOURCE__
