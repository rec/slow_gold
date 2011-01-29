#ifndef __REC_SLOW_APP_STRETCHYPLAYER__
#define __REC_SLOW_APP_STRETCHYPLAYER__

#include "rec/util/thread/ChangeLocker.h"
#include "rec/audio/source/DoubleRunnyBuffer.h"
#include "rec/audio/stretch/Stretchy.pb.h"
#include "rec/util/listener/SetterListener.h"

namespace rec {
namespace slow {

class AudioTransportSourcePlayer;

class StretchyPlayer : public Listener<const VirtualFile&>,
                       public Listener<const float&>,
                       public Broadcaster<const VirtualFile&> {
 public:
  typedef audio::stretch::StretchyLoop StretchyLoop;
  typedef audio::stretch::StretchyProto StretchyProto;

  explicit StretchyPlayer(AudioDeviceManager* deviceManager);
  virtual ~StretchyPlayer();

  // Callback when we get a new file.
  virtual void operator()(const VirtualFile& file);

  // Callback when we're ready to actually jump to a new time.
  virtual void operator()(const float& time);

  void setTime(int time) { timeLocker_->set(time); }

  Listener<const VirtualFile&>* fileListener() { return &fileListener_; }
  AudioTransportSourcePlayer* getTransport() { return transportSource_.get(); }

  persist::Data<StretchyLoop>* getStretchy() { return stretchy_; }
  gui::CachedThumbnail* cachedThumbnail() {
    return doubleRunny_? doubleRunny_->cachedThumbnail() : NULL;
  }

  int length() const {
    return doubleRunny_ ? doubleRunny_->getTotalLength() : 0;
  }

 private:
  typedef thread::ChangeLocker<float> TimeLocker;
  typedef thread::ChangeLocker<VirtualFile> FileLocker;

  thread_ptr<AudioTransportSourcePlayer> transportSource_;

  CriticalSection lock_;
  VirtualFile file_;
  persist::Data<StretchyLoop>* stretchy_;
  thread_ptr<TimeLocker> timeLocker_;
  thread_ptr<FileLocker> fileLocker_;

  SetterListener<const VirtualFile&> fileListener_;
  thread_ptr<audio::source::DoubleRunnyBuffer> doubleRunny_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(StretchyPlayer);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_APP_STRETCHYPLAYER__
