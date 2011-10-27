#ifndef __REC_SLOW_MODEL__
#define __REC_SLOW_MODEL__

#include "rec/audio/source/FrameSource.h"
#include "rec/audio/source/Selection.h"
#include "rec/audio/stretch/Stretch.pb.h"
#include "rec/audio/util/ThumbnailBuffer.h"
#include "rec/data/Data.h"
#include "rec/music/Metadata.pb.h"
#include "rec/slow/CurrentFile.h"
#include "rec/slow/Components.h"
#include "rec/slow/HasInstance.h"
#include "rec/util/LoopPoint.h"
#include "rec/util/LoopPoint.pb.h"
#include "rec/util/Mode.pb.h"
#include "rec/util/block/Block.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/util/listener/DataListener.h"
#include "rec/util/listener/Listener.h"
#include "rec/util/thread/Result.h"
#include "rec/widget/waveform/Zoom.pb.h"

namespace rec {

namespace gui { class DropFiles; }

namespace slow {

class Instance;

class Model : public Listener< Samples<44100> >,
              public HasInstance {
 public:
  typedef audio::stretch::Stretch Stretch;
  typedef music::Metadata Metadata;
  typedef widget::waveform::ZoomProto ZoomProto;

  typedef audio::util::ThumbnailBuffer ThumbnailBuffer;

  explicit Model(Instance* i);
  virtual ~Model();

  void clear();

  virtual void operator()(Samples<44100> t) { ScopedLock l(lock_); time_ = t; }
  virtual void setLoopPointList(const LoopPointList&);

  void zoom(RealTime time, double k);
  void zoom(double k);

  thread::Result fillOnce();
  void jumpToTime(Samples<44100>);
  void setCursorTime(int index, RealTime time);

  bool empty() const { return file::empty(file()); }

  ThumbnailBuffer* thumbnailBuffer() { return &thumbnailBuffer_; }

 private:
  CriticalSection lock_;

  Samples<44100> time_;
  Samples<44100> triggerPosition_;
  block::BlockSet timeSelection_;
  ThumbnailBuffer thumbnailBuffer_;

  AudioSampleBuffer updateBuffer_;
  AudioSourceChannelInfo updateInfo_;
  audio::source::FrameSource<short, 2> updateSource_;

  typedef DataListener<LoopPointList> LoopListener;
  ptr<LoopListener> loopListener_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Model);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_MODEL__
