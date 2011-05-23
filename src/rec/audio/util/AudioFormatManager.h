#ifndef __REC_AUDIO_AUDIOFORMATMANAGER__
#define __REC_AUDIO_AUDIOFORMATMANAGER__

#include "rec/base/base.h"

namespace rec {
namespace audio {

AudioFormatManager* getAudioFormatManager();

AudioFormatReader* createReader(const File&);
AudioFormatReader* createReader(const VirtualFile&);
AudioFormatReader* createReader(const String&);
AudioFormatReader* createReader(const string&);

}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_AUDIOFORMATMANAGER__
