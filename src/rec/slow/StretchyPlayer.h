#ifndef __REC_SLOW_APP_STRETCHYPLAYER__
#define __REC_SLOW_APP_STRETCHYPLAYER__

#include "rec/util/thread/ChangeLocker.h"
#include "rec/audio/source/DoubleRunnyBuffer.h"
#include "rec/audio/stretch/Stretch.pb.h"
#include "rec/util/listener/SetterListener.h"

namespace rec {
namespace slow {

class AudioTransportSourcePlayer;

class StretchyPlayer : public Listener<const VirtualFile&>,
                       public Listener<const double&>,
                       public Listener<double>,
                       public Broadcaster<const VirtualFile&> {
 public:
  typedef audio::stretch::StretchLoop StretchLoop;

  explicit StretchyPlayer(AudioDeviceManager* deviceManager);
  virtual ~StretchyPlayer();

  // Callback when we get a new file.
  virtual void operator()(const VirtualFile& file);

  // Callback when we're ready to actually jump to a new time.
  virtual void operator()(const double& time);

  // Callback to set the new time.
  virtual void operator()(double time) { setTime(time); }

  void setTime(double time) {
    DLOG(INFO) << time;
    timeLocker_->set(time);
  }

  Listener<const VirtualFile&>* fileListener() { return &fileListener_; }
  AudioTransportSourcePlayer* getTransport() {
	  return transportSource_.get();
  }

  persist::Data<StretchLoop>* getStretchy() { return stretchy_; }
  gui::CachedThumbnail* cachedThumbnail();
  int length() const;

 private:
  typedef thread::ChangeLocker<double> TimeLocker;
  typedef thread::ChangeLocker<VirtualFile> FileLocker;

  thread_ptr<AudioTransportSourcePlayer> transportSource_;

  CriticalSection lock_;
  VirtualFile file_;
  persist::Data<StretchLoop>* stretchy_;
  thread_ptr<TimeLocker> timeLocker_;
  thread_ptr<FileLocker> fileLocker_;

  SetterListener<const VirtualFile&> fileListener_;
  thread_ptr<audio::source::DoubleRunnyBuffer> doubleRunny_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(StretchyPlayer);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_APP_STRETCHYPLAYER__
