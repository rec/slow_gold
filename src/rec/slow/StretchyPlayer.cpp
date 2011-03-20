#include "rec/slow/StretchyPlayer.h"
#include "rec/audio/source/DoubleRunnyBuffer.h"
#include "rec/data/proto/Equals.h"
#include "rec/slow/AudioTransportSourcePlayer.h"

namespace rec {
namespace slow {

static const int CHANGE_LOCKER_WAIT = 100;

StretchyPlayer::StretchyPlayer(AudioDeviceManager* deviceManager)
    : transportSource_(new AudioTransportSourcePlayer(deviceManager)),
      stretchy_(NULL),
      timeLocker_(new TimeLocker(CHANGE_LOCKER_WAIT)),
      fileLocker_(new FileLocker(CHANGE_LOCKER_WAIT)),
      fileListener_(persist::data<VirtualFile>()) {
  fileLocker_->addListener(this);
  timeLocker_->addListener(this);

  persist::data<VirtualFile>()->addListener(fileLocker_.get());

  fileLocker_->startThread();
  timeLocker_->startThread();
  transportSource_->update();
}

StretchyPlayer::~StretchyPlayer() {
  transportSource_->clear();
}

void StretchyPlayer::operator()(const VirtualFile& file) {
  {
    ScopedLock l(lock_);
    if (file_ == file)
      return;
  }

  persist::Data<StretchLoop>* stretchy = NULL;
  thread_ptr<audio::source::DoubleRunnyBuffer> dr;
  if (!empty(file)) {
    stretchy = persist::data<StretchLoop>(file);
    dr.reset(new audio::source::DoubleRunnyBuffer(file, stretchy));
  }

  {
    ScopedLock l(lock_);
    file_ = file;
    timeLocker_->initialize(0);
    transportSource_->clear();
    dr.swap(doubleRunny_);
    transportSource_->setSource(doubleRunny_->doubleStretchy());
    stretchy_ = stretchy;
    if (stretchy_)
      stretchy_->requestUpdate();
  }

  broadcast(file);
}

void StretchyPlayer::operator()(const double& t) {
  // This is only called when the user clicks in the window to set a new
  // playback position.
  if (stretchy_ && (!doubleRunny_ || doubleRunny_->fillFromPosition(44100 * t)))
    transportSource_->setPosition(stretchy_->get().stretch().time_scale() * t);

  else
    LOG(ERROR) << "Failed to fill buffer.";
}

gui::CachedThumbnail* StretchyPlayer::cachedThumbnail() {
  return doubleRunny_? doubleRunny_->cachedThumbnail() : NULL;
}

int StretchyPlayer::length() const {
  return doubleRunny_ ? doubleRunny_->getTotalLength() : 0;
}

}  // namespace slow
}  // namespace rec
