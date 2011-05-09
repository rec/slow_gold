#ifndef __REC_AUDIO_SOURCE_DOUBLERUNNYBUFFER__
#define __REC_AUDIO_SOURCE_DOUBLERUNNYBUFFER__

#include "rec/audio/source/Runny.pb.h"
#include "rec/audio/source/Switching.h"
#include "rec/audio/stretch/Stretch.pb.h"
#include "rec/audio/util/CachedThumbnail.h"
#include "rec/audio/util/FillableBuffer.h"
#include "rec/data/persist/Persist.h"
#include "rec/util/thread/ChangeLocker.h"

namespace rec {
namespace audio {
namespace source {

class DoubleRunnyBuffer : public Thread,
                          public Listener<const stretch::StretchLoop&> {
 public:
  typedef stretch::StretchLoop StretchLoop;
  typedef persist::Data<StretchLoop> Data;

  DoubleRunnyBuffer(const VirtualFile& file, Data* data,
                    const RunnyProto& desc = RunnyProto::default_instance());
  virtual ~DoubleRunnyBuffer();

  bool fillFromPosition(int pos);

  gui::CachedThumbnail* cachedThumbnail() { return cachedThumbnail_.get(); }
  virtual int64 getTotalLength() const { return buffer_->getLength(); }

  virtual void operator()(const StretchLoop& p);
  bool empty() const { return empty_; }

  virtual void run();
  Data* data() { return data_; }
  bool waitUntilFilled(uint32 readahead);
  Switching* doubleStretchy() { return &switching_; }

 private:
  typedef thread::ChangeLocker<StretchLoop> ChangeLocker;

  void setLoop(const StretchLoop& loop) { (*this)(loop); }

  CriticalSection lock_;

  Switching switching_;
  StretchLoop stretchLoop_;
  const RunnyProto runnyDesc_;
  ptr<FillableBuffer> buffer_;
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
