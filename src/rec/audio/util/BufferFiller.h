#ifndef __REC_AUDIO_UTIL_BUFFERFILLER__
#define __REC_AUDIO_UTIL_BUFFERFILLER__

#include "rec/audio/Audio.h"
#include "rec/util/block/Block.h"

namespace rec {
namespace audio {
namespace util {

class BufferedReader;
class CachedThumbnail;

class BufferFiller {
 public:
  BufferFiller();
  virtual ~BufferFiller();

  block::Block fillOnce();
  bool isFull() const;
  SampleTime setReader(const VirtualFile& file, AudioFormatReader* r);
  audio::util::BufferedReader* reader() { return reader_.get(); }
  AudioThumbnail* thumbnail();
  void reset();

 private:
  CriticalSection lock_;

  ptr<CachedThumbnail> thumbnail_;
  ptr<BufferedReader> reader_;
  File file_;

  AudioSampleBuffer updateBuffer_;
  AudioSourceChannelInfo updateInfo_;
  ptr<audio::Source> updateSource_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(BufferFiller);
};

}  // namespace util
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_UTIL_BUFFERFILLER__
