#ifndef __REC_SLOW_BUFFERFILLER__
#define __REC_SLOW_BUFFERFILLER__

#include "rec/audio/source/FrameSource.h"
#include "rec/audio/source/Selection.h"
#include "rec/audio/stretch/Stretch.pb.h"
#include "rec/audio/util/TrackBufferAndThumbnail.h"
#include "rec/data/Data.h"
#include "rec/slow/Components.h"
#include "rec/slow/HasInstance.h"
#include "rec/util/LoopPoint.h"
#include "rec/util/Mode.pb.h"
#include "rec/util/block/Block.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/data/DataListener.h"
#include "rec/util/Listener.h"
#include "rec/util/thread/Result.h"
#include "rec/widget/waveform/Zoom.pb.h"

namespace rec {
namespace slow {

class Instance;

class BufferFiller : public HasInstance {
 public:
  typedef audio::stretch::Stretch Stretch;
  typedef audio::util::TrackBufferAndThumbnail TrackBufferAndThumbnail;

  explicit BufferFiller(Instance* i);
  virtual ~BufferFiller();

  void fillOnce();
  TrackBufferAndThumbnail* trackBuffer() { return &trackBuffer_; }
  bool isFull() const;

 private:
  CriticalSection lock_;

  Samples<44100> triggerPosition_;
  TrackBufferAndThumbnail trackBuffer_;

  AudioSampleBuffer updateBuffer_;
  AudioSourceChannelInfo updateInfo_;
  ptr<audio::Source> updateSource_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(BufferFiller);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_BUFFERFILLER__
