#ifndef __REC_AUDIO_SOURCE_DOUBLERUNNYBUFFER__
#define __REC_AUDIO_SOURCE_DOUBLERUNNYBUFFER__

#include "rec/audio/source/Buffery.h"
#include "rec/audio/source/BufferySource.h"
#include "rec/audio/source/CachedThumbnail.h"
#include "rec/audio/source/DoubleRunny.h"
#include "rec/data/persist/Data.h"

namespace rec {
namespace audio {
namespace source {

class DoubleRunnyBuffer
  : public DoubleRunny,
    public Thread,
    public listener::Listener<const StretchyProto&>,
    public listener::Listener<const Buffery&> {

 public:
  typedef persist::Data<StretchyProto> Data;
  DoubleRunnyBuffer(const VolumeFile& file, Data* data);
  virtual ~DoubleRunnyBuffer();

  static const int READAHEAD = 20000;
  static const int WAIT_TIME = 20;
  static const int MAX_WAIT_TIME = 7000;

  Buffery* buffery() { return buffery_.get(); }

  virtual PositionableAudioSource* makeSource(const VolumeFile& f);
  juce::AudioThumbnail* thumbnail() { return cachedThumbnail_->thumbnail(); }
  CachedThumbnail* cachedThumbnail() { return cachedThumbnail_.get(); }

  virtual void operator()(const StretchyProto& p) {
    if (changeLocker_)
      changeLocker_->set(p);
    else
      LOG(ERROR) << "Empty changelocker";
  }

  virtual void operator()(const Buffery&);

  virtual void run();
  Data* data() { return data_; }

 private:
  typedef thread::ChangeLocker<StretchyProto> ChangeLocker;

  ptr<Buffery> buffery_;
  ptr<CachedThumbnail> cachedThumbnail_;
  persist::Data<StretchyProto>* const data_;
  ptr<ChangeLocker> changeLocker_;

  DISALLOW_COPY_AND_ASSIGN(DoubleRunnyBuffer);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_DOUBLERUNNYBUFFER__
