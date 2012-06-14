#ifndef __REC_AUDIO_AUDIOFORMATMANAGER__
#define __REC_AUDIO_AUDIOFORMATMANAGER__

#include "rec/base/base.h"

namespace rec {
namespace audio {
namespace format {

AudioFormatManager* getReaderAudioFormatManager();
AudioFormatManager* getWriterAudioFormatManager();

AudioFormatReader* createReader(const File&);
AudioFormatReader* createReader(const String&);
AudioFormatWriter* createWriter(const File&);

}  // namespace format
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_AUDIOFORMATMANAGER__
