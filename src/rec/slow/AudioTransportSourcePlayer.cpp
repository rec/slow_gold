#include "rec/slow/AudioTransportSourcePlayer.h"
#include "rec/util/Math.h"

namespace rec {
namespace slow {

static const double MINIMUM_BROADCAST_TIMECHANGE = 0.001;
static const float SAMPLE_RATE = 44100.0f;

AudioTransportSourcePlayer::AudioTransportSourcePlayer(AudioDeviceManager* dm)
    : Thread("AudioTransportSourcePlayer"),
      deviceManager_(dm),
      lastTime_(-1.0),
      offset_(0.0) {
  deviceManager_->addAudioCallback(&audioSourcePlayer_);
  audioSourcePlayer_.setSource(audioTransportSource());
  audioTransportSource_.addChangeListener(this);
}

void AudioTransportSourcePlayer::run() {
  while (!threadShouldExit()) {
    broadcastTimeIfChanged();
    if (!threadShouldExit())
      wait(THREAD_WAIT);
  }
}

void AudioTransportSourcePlayer::broadcastTimeIfChanged() {
  ScopedLock l(lock_);
  double time = audioTransportSource_.getNextReadPosition() / SAMPLE_RATE;
  if (!Math<double>::near(time, lastTime_, MINIMUM_BROADCAST_TIMECHANGE)) {
    lastTime_ = time;
    doubleBroadcaster_.broadcast(time + offset_);
  }
}

AudioTransportSourcePlayer::~AudioTransportSourcePlayer() {
  clear();
  deviceManager_->removeAudioCallback(&audioSourcePlayer_);
  audioSourcePlayer_.setSource(NULL);
}

void AudioTransportSourcePlayer::clear() {
  audioTransportSource_.stop();
  audioTransportSource_.setSource(NULL);

  signalThreadShouldExit();
}

void AudioTransportSourcePlayer::setPosition(double newPosition) {
  if (audioTransportSource_.isPlaying() &&
      (newPosition < offset_ ||
       newPosition >= offset_ + audioTransportSource_.getLengthInSeconds())) {
    newPosition = offset_;
  }

  audioTransportSource_.setPosition(newPosition - offset_);
  broadcastTimeIfChanged();
}

void AudioTransportSourcePlayer::setOffset(double offset) {
  ScopedLock l(lock_);
  offset_ = offset;
}

void AudioTransportSourcePlayer::setStart(bool isStart) {
  if (isStart) {
    double pos = audioTransportSource_.getCurrentPosition();
    if (pos <= offset_ || pos >= offset_ + audioTransportSource_.getLengthInSeconds())
      setPosition(offset_);

    startThread();

    audioTransportSource_.start();
  } else {
    audioTransportSource_.stop();
  }
}

}  // namespace slow
}  // namespace rec
