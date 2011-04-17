#ifdef TODO
#ifndef __REC_SLOW_APP_STRETCHYPLAYER__
#define __REC_SLOW_APP_STRETCHYPLAYER__

#include "rec/util/thread/ChangeLocker.h"
#include "rec/audio/source/DoubleRunnyBuffer.h"
#include "rec/audio/stretch/Stretch.pb.h"
#include "rec/util/listener/SetterListener.h"

namespace rec {
namespace slow {

class AudioTransportSourcePlayer;

class StretchyPlayer {
 public:
  typedef audio::stretch::StretchLoop StretchLoop;

  explicit StretchyPlayer(Instance* instance);
  virtual ~StretchyPlayer();

  void setTime(double time) {
    DLOG(INFO) << time;
    timeLocker_->set(time);
  }

 private:
  typedef thread::ChangeLocker<double> TimeLocker;
  typedef thread::ChangeLocker<VirtualFile> FileLocker;

  CriticalSection lock_;
  Instance* instance_;
  VirtualFile file_;

  thread_ptr<TimeLocker> timeLocker_;
  thread_ptr<FileLocker> fileLocker_;

  thread_ptr<audio::source::DoubleRunnyBuffer> doubleRunny_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(StretchyPlayer);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_APP_STRETCHYPLAYER__
#endif
