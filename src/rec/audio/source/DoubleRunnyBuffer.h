#ifndef __REC_AUDIO_SOURCE_DOUBLERUNNYBUFFER__
#define __REC_AUDIO_SOURCE_DOUBLERUNNYBUFFER__

#include "rec/audio/source/Buffery.h"
#include "rec/audio/source/BufferySource.h"
#include "rec/audio/source/CachedThumbnail.h"
#include "rec/audio/source/DoubleRunny.h"
#include "rec/data/persist/Persist.h"

namespace rec {
namespace audio {
namespace source {

class DoubleRunnyBuffer
  : public DoubleRunny,
    public Thread,
    public listener::Listener<const StretchyProto&> {
 public:
  typedef persist::Data<StretchyProto> Data;

  DoubleRunnyBuffer(const VolumeFile& file, Data* data);
  virtual ~DoubleRunnyBuffer() {}

  bool fillFromPosition(int pos);

  virtual PositionableAudioSource* makeSource();
  juce::AudioThumbnail* thumbnail() { return cachedThumbnail_->thumbnail(); }
  CachedThumbnail* cachedThumbnail() { return cachedThumbnail_.get(); }

  virtual void operator()(const StretchyProto& p);

  bool empty() const { return empty_; }

  virtual void run();
  Data* data() { return data_; }

 private:
  typedef thread::ChangeLocker<StretchyProto> ChangeLocker;

  ptr<Buffery> buffery_;
  ptr<CachedThumbnail> cachedThumbnail_;
  Data* const data_;
  thread_ptr<ChangeLocker> changeLocker_;
  bool empty_;

  DISALLOW_COPY_AND_ASSIGN(DoubleRunnyBuffer);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_DOUBLERUNNYBUFFER__
