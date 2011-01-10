#ifndef __REC_SLOW_APP_STRETCHYPLAYER__
#define __REC_SLOW_APP_STRETCHYPLAYER__

#include "rec/util/thread/ChangeLocker.h"
#include "rec/audio/source/DoubleRunnyBuffer.h"
#include "rec/audio/source/Stretchy.pb.h"
#include "rec/util/listener/SetterListener.h"

namespace rec {
namespace slow {

class AudioTransportSourcePlayer;

class StretchyPlayer : public Listener<const VolumeFile&>,
                       public Listener<const float&>,
                       public Broadcaster<const VolumeFile&> {
 public:
  typedef audio::source::StretchyProto StretchyProto;

  explicit StretchyPlayer(AudioDeviceManager* deviceManager);
  virtual ~StretchyPlayer();

  // Callback when we get a new file.
  virtual void operator()(const VolumeFile& file);

  // Callback when we're ready to actually jump to a new time.
  virtual void operator()(const float& time);

  void setTime(int time) {
    // thread::callAsync(timeLocker_.get(), &TimeLocker::set, timeMouse.time_);
    timeLocker_->set(time);
  }

  Listener<const VolumeFile&>* fileListener() { return &fileListener_; }
  AudioTransportSourcePlayer* getTransport() { return transportSource_.get(); }

  persist::Data<StretchyProto>* getStretchy() { return stretchy_; }
  gui::CachedThumbnail* cachedThumbnail() {
    return doubleRunny_? doubleRunny_->cachedThumbnail() : NULL;
  }

  int length() const {
    return doubleRunny_ ? doubleRunny_->getTotalLength() : 0;
  }

 private:
  typedef thread::ChangeLocker<float> TimeLocker;
  typedef thread::ChangeLocker<VolumeFile> FileLocker;

  thread_ptr<AudioTransportSourcePlayer> transportSource_;

  CriticalSection lock_;
  VolumeFile file_;
  persist::Data<StretchyProto>* stretchy_;
  thread_ptr<TimeLocker> timeLocker_;
  thread_ptr<FileLocker> fileLocker_;

  SetterListener<const VolumeFile&> fileListener_;
  thread_ptr<audio::source::DoubleRunnyBuffer> doubleRunny_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(StretchyPlayer);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_APP_STRETCHYPLAYER__
