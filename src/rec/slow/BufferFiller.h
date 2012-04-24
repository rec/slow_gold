#ifndef __REC_SLOW_BUFFERFILLER__
#define __REC_SLOW_BUFFERFILLER__

#include "rec/audio/Audio.h"
#include "rec/util/block/Block.h"
#include "rec/util/file/VirtualFile.h"

namespace rec {

namespace audio { namespace util { class BufferedReader; }}
namespace audio { namespace util { class CachedThumbnail; }}

namespace slow {

class Instance;
class CurrentTime;

class BufferFiller {
 public:
  BufferFiller();
  virtual ~BufferFiller();

  block::Block fillOnce(CurrentTime*);
  bool isFull() const;
  Samples<44100> setReader(const VirtualFile& file, AudioFormatReader* r);
  audio::util::BufferedReader* reader() { return reader_.get(); }
  AudioThumbnail* thumbnail();

 private:
  CriticalSection lock_;

  ptr<audio::util::CachedThumbnail> thumbnail_;
  ptr<audio::util::BufferedReader> reader_;
  File file_;

  AudioSampleBuffer updateBuffer_;
  AudioSourceChannelInfo updateInfo_;
  ptr<audio::Source> updateSource_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(BufferFiller);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_BUFFERFILLER__
