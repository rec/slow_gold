#include "rec/slow/AudioTransportSourcePlayer.h"

namespace rec {
namespace slow {

AudioTransportSourcePlayer::AudioTransportSourcePlayer(AudioDeviceManager* dm)
: Thread("AudioTransportSourcePlayer"), deviceManager_(dm) {
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
}

void AudioTransportSourcePlayer::setPosition(double newPosition) {
  AudioTransportSource::setPosition(newPosition);
  update();
}

void AudioTransportSourcePlayer::update() {
  broadcast(getNextReadPosition() / 44100.0f);
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
