#ifndef __REC_SLOW_MODEL__
#define __REC_SLOW_MODEL__

#include "rec/audio/stretch/Stretch.pb.h"
#include "rec/audio/source/Selection.h"
#include "rec/audio/source/Stereo.h"
#include "rec/audio/util/ThumbnailBuffer.h"
#include "rec/data/persist/Persist.h"
#include "rec/gui/audio/LoopPoint.pb.h"
#include "rec/slow/HasInstance.h"
#include "rec/music/Metadata.pb.h"
#include "rec/util/Switcher.h"
#include "rec/util/block/Block.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/util/listener/Listener.h"
#include "rec/util/thread/Locker.h"
#include "rec/slow/Components.h"
#include "rec/widget/waveform/Zoom.pb.h"

namespace rec {
namespace slow {

class Instance;

class Model : public Listener<const VirtualFile&>,
              public Listener<SampleTime>,
              public HasInstance {
 public:
  typedef audio::source::StereoProto StereoProto;
  typedef audio::stretch::Stretch Stretch;
  typedef music::Metadata Metadata;
  typedef gui::audio::LoopPointList LoopPointList;
  typedef widget::waveform::ZoomProto ZoomProto;

  explicit Model(Instance* i);
  virtual ~Model() {}

  virtual void operator()(const VirtualFile& vf);
  virtual void operator()(SampleTime t) { ScopedLock l(lock_); time_ = t; }

  thread::Locker<VirtualFile>* fileLocker() { return &fileLocker_; }
  thread::Locker<ZoomProto>* zoomLocker() { return &zoomLocker_; }
  void zoom(RealTime time, double k);

  void setLoopPointList(const gui::audio::LoopPointList& vf);
  void checkChanged();
  void fillOnce();
  void setTriggerTime(SampleTime p);
  Switcher<audio::util::ThumbnailBuffer>* thumbnailBuffer() { return &thumbnailBuffer_; }
  void toggleSelectionSegment(RealTime time);
  void setCursorTime(int index, RealTime time);

 private:
  bool hasTriggerTime(SampleTime t);

  CriticalSection lock_;

  thread::Locker<VirtualFile> fileLocker_;
  VirtualFile file_;

  thread::Locker<LoopPointList> loopLocker_;
  thread::Locker<Metadata> metadataLocker_;
  thread::Locker<StereoProto> stereoLocker_;
  thread::Locker<Stretch> stretchLocker_;
  thread::Locker<ZoomProto> zoomLocker_;

  SampleTime time_;
  SampleTime triggerTime_;
  block::BlockSet timeSelection_;

  Switcher<audio::util::ThumbnailBuffer> thumbnailBuffer_;
  persist::Data<LoopPointList>* loopData_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Model);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_MODEL__
