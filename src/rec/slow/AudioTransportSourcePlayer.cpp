#include "rec/slow/AudioTransportSourcePlayer.h"
#include "rec/util/Math.h"

namespace rec {
namespace slow {

AudioTransportSourcePlayer::AudioTransportSourcePlayer(AudioDeviceManager* dm)
    : Thread("AudioTransportSourcePlayer"),
      deviceManager_(dm),
      lastTime_(-1.0),
      offset_(0.0) {
  deviceManager_->addAudioCallback(&player_);
  player_.setSource(this);
  addChangeListener(this);  // Listen to ourselves!
}

AudioTransportSourcePlayer::~AudioTransportSourcePlayer() {
  clear();
  deviceManager_->removeAudioCallback(&player_);
  player_.setSource(NULL);
}

void AudioTransportSourcePlayer::clear() {
  stop();
  setSource(NULL);
  signalThreadShouldExit();
}

void AudioTransportSourcePlayer::setPosition(double newPosition) {
  if (isPlaying() && (newPosition < offset_ || newPosition >= offset_ + getLengthInSeconds()))
    newPosition = offset_;
  AudioTransportSource::setPosition(newPosition - offset_);
  update();
}

void AudioTransportSourcePlayer::update() {
  ScopedLock l(lock_);
  double time = getNextReadPosition() / 44100.0f;
  if (!Math<double>::near(time, lastTime_, 0.1)) {
    lastTime_ = time;
    broadcast(time + offset_);
  }
}

void AudioTransportSourcePlayer::setOffset(double offset) {
  ScopedLock l(lock_);
  offset_ = offset;
}

void AudioTransportSourcePlayer::setStart(bool isStart) {
  if (isStart) {
    double pos = getCurrentPosition();
    // DLOG(INFO) << "POS! " << pos;
    if (pos < offset_ || pos >= offset_ + getLengthInSeconds())
      setPosition(offset_);
    startThread();

    AudioTransportSource::start();
  } else {
    AudioTransportSource::stop();
  }
}

void AudioTransportSourcePlayer::run() {
  while (!threadShouldExit()) {
    update();
    if (!threadShouldExit())
      wait(THREAD_WAIT);
  }
}

}  // namespace slow
}  // namespace rec
