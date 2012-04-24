#ifndef __REC_SLOW_BUFFERFILLER__
#define __REC_SLOW_BUFFERFILLER__

#include "rec/audio/source/FrameSource.h"
#include "rec/audio/source/Selection.h"
#include "rec/audio/stretch/Stretch.pb.h"
#include "rec/audio/util/BufferedReader.h"
#include "rec/audio/util/CachedThumbnail.h"
#include "rec/data/Data.h"
#include "rec/data/DataListener.h"
#include "rec/slow/Components.h"
#include "rec/slow/HasInstance.h"
#include "rec/util/Listener.h"
#include "rec/util/LoopPoint.h"
#include "rec/util/Mode.pb.h"
#include "rec/util/block/Block.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/util/thread/Result.h"
#include "rec/widget/waveform/Zoom.pb.h"

namespace rec {
namespace slow {

class Instance;

class BufferFiller {
 public:
  typedef audio::stretch::Stretch Stretch;

  BufferFiller();
  virtual ~BufferFiller();

  block::Block fillOnce(CurrentTime*);
  bool isFull() const;
  Samples<44100> setReader(const VirtualFile& file, AudioFormatReader* r);
  audio::util::BufferedReader* reader() { return reader_.get(); }
  AudioThumbnail* thumbnail() { return thumbnail_.thumbnail(); }

 private:
  CriticalSection lock_;

  audio::util::CachedThumbnail thumbnail_;
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
