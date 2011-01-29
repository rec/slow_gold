#ifndef __REC_AUDIO_SOURCE_DOUBLERUNNYBUFFER__
#define __REC_AUDIO_SOURCE_DOUBLERUNNYBUFFER__

#include "rec/audio/util/FillableBuffer.h"
#include "rec/audio/source/DoubleStretchyRunny.h"
#include "rec/data/persist/Persist.h"
#include "rec/gui/CachedThumbnail.h"
#include "rec/util/thread/ChangeLocker.h"

namespace rec {
namespace audio {
namespace source {

class DoubleRunnyBuffer : public DoubleStretchyRunny,
                          public Thread,
                          public Listener<const stretch::StretchLoop&> {
 public:
  typedef stretch::StretchLoop StretchLoop;
  typedef persist::Data<StretchLoop> Data;

  DoubleRunnyBuffer(const VirtualFile& file, Data* data,
                    const RunnyProto& desc = RunnyProto::default_instance());
  virtual ~DoubleRunnyBuffer();

  bool fillFromPosition(int pos);

  virtual PositionableAudioSource* makeSource();
  gui::CachedThumbnail* cachedThumbnail() { return cachedThumbnail_.get(); }
  virtual int64 getTotalLength() const { return buffery_->getLength(); }

  virtual void operator()(const StretchLoop& p) { setLoop(p); }

  bool empty() const { return empty_; }

  virtual void run();
  Data* data() { return data_; }

 private:
  typedef thread::ChangeLocker<StretchLoop> ChangeLocker;

  ptr<FillableBuffer> buffery_;
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
