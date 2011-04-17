#ifdef TODO

#include "rec/slow/StretchyPlayer.h"
#include "rec/audio/source/DoubleRunnyBuffer.h"
#include "rec/data/proto/Equals.h"
#include "rec/slow/AudioTransportSourcePlayer.h"

namespace rec {
namespace slow {

static const int CHANGE_LOCKER_WAIT = 100;

StretchyPlayer::StretchyPlayer(AudioDeviceManager* deviceManager)
    : timeLocker_(new TimeLocker(CHANGE_LOCKER_WAIT)),
      fileLocker_(new FileLocker(CHANGE_LOCKER_WAIT)) {
  fileLocker_->addListener(this);
  timeLocker_->addListener(this);

  persist::data<VirtualFile>()->addListener(fileLocker_.get());

  fileLocker_->startThread();
  timeLocker_->startThread();
  transportSource_->broadcastTimeIfChanged();
}

StretchyPlayer::~StretchyPlayer() {
  transportSource_->clear();
}

}  // namespace slow
}  // namespace rec

#endif
