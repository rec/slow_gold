#include "rec/slow/AudioTransportSourcePlayer.h"
#include "rec/util/Math.h"

namespace rec {
namespace slow {

AudioTransportSourcePlayer::AudioTransportSourcePlayer(AudioDeviceManager* dm)
    : Thread("AudioTransportSourcePlayer"), deviceManager_(dm), lastTime_(-1.0) {
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
  AudioTransportSource::setPosition(newPosition);
  update();
}

void AudioTransportSourcePlayer::update() {
  float time = getNextReadPosition() / 44100.0f;
  if (!Math<float>::near(time, lastTime_, 0.1)) {
    lastTime_ = time;
    broadcast(time);
  }
}

void AudioTransportSourcePlayer::setStart(bool isStart) {
  if (isStart) {
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
