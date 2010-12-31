#ifndef __REC_AUDIO_SOURCE_DOUBLERUNNYBUFFER__
#define __REC_AUDIO_SOURCE_DOUBLERUNNYBUFFER__

#include "rec/audio/source/Buffery.h"
#include "rec/audio/source/DoubleStretchyRunny.h"
#include "rec/data/persist/Persist.h"
#include "rec/gui/CachedThumbnail.h"
#include "rec/util/thread/ChangeLocker.h"

namespace rec {
namespace audio {
namespace source {

class DoubleRunnyBuffer
  : public DoubleStretchyRunny,
    public Thread,
    public Listener<const StretchyProto&> {
 public:
  typedef persist::Data<StretchyProto> Data;

  DoubleRunnyBuffer(const VolumeFile& file, Data* data,
                    const RunnyProto& desc = RunnyProto::default_instance());
  virtual ~DoubleRunnyBuffer();

  bool fillFromPosition(int pos);

  virtual PositionableAudioSource* makeSource();
  gui::CachedThumbnail* cachedThumbnail() { return cachedThumbnail_.get(); }

  virtual void operator()(const StretchyProto& p) { setStretchy(p); }

  bool empty() const { return empty_; }

  virtual void run();
  Data* data() { return data_; }

 private:
  typedef thread::ChangeLocker<StretchyProto> ChangeLocker;

  ptr<Buffery> buffery_;
  ptr<gui::CachedThumbnail> cachedThumbnail_;
  Data* const data_;
  thread_ptr<ChangeLocker> changeLocker_;
  bool empty_;

  DISALLOW_COPY_AND_ASSIGN(DoubleRunnyBuffer);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_DOUBLERUNNYBUFFER__
