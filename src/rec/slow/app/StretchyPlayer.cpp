#include "rec/slow/app/StretchyPlayer.h"
#include "rec/slow/app/AudioTransportSourcePlayer.h"
#include "rec/data/proto/Equals.h"
#include "rec/audio/source/DoubleRunnyBuffer.h"

namespace rec {
namespace slow {

static const int CHANGE_LOCKER_WAIT = 100;

StretchyPlayer::StretchyPlayer(AudioDeviceManager* deviceManager)
    : transportSource_(new AudioTransportSourcePlayer(deviceManager)),
      stretchy_(NULL),
      timeLocker_(new TimeLocker(CHANGE_LOCKER_WAIT)),
      fileLocker_(new FileLocker(CHANGE_LOCKER_WAIT)),
      fileListener_(persist::data<VolumeFile>()) {
  fileLocker_->addListener(this);
  timeLocker_->addListener(this);

  persist::data<VolumeFile>()->addListener(fileLocker_.get());

  fileLocker_->startThread();
  timeLocker_->startThread();
  transportSource_->update();
}

StretchyPlayer::~StretchyPlayer() {
  transportSource_->clear();
}

void StretchyPlayer::operator()(const VolumeFile& file) {
  {
    ScopedLock l(lock_);
    if (file_ == file)
      return;
  }

  persist::Data<StretchyProto>* stretchy = NULL;
  thread_ptr<audio::source::DoubleRunnyBuffer> dr;
  if (!empty(file)) {
    stretchy = persist::data<StretchyProto>(file);
    dr.reset(new audio::source::DoubleRunnyBuffer(file, stretchy));
  }

  {
    ScopedLock l(lock_);
    file_ = file;
    timeLocker_->initialize(0);
    transportSource_->clear();
    dr.swap(doubleRunny_);
    if (stretchy_)
      stretchy_->requestUpdate();
  }

  broadcast(file);
}

void StretchyPlayer::operator()(const float& time) {
  if (!doubleRunny_ || doubleRunny_->fillFromPosition(44100.0 * time))
    transportSource_->setPosition(stretchy_->get().time_scale() * time);

  else
    LOG(ERROR) << "Failed to fill buffer.";
}

}  // namespace slow
}  // namespace rec
