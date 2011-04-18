#include "rec/slow/AudioTransportSourcePlayer.h"
#include "rec/util/Math.h"

namespace rec {
namespace slow {

static const double MINIMUM_BROADCAST_TIMECHANGE = 0.001;
static const float SAMPLE_RATE = 44100.0f;

Player::Player(Device* d)
    : Thread("Player"),
      device_(d),
      lastTime_(-1.0) {
  device_->manager_.addAudioCallback(&sourcePlayer_);
  sourcePlayer_.setSource(transportSource());
  transportSource_.addChangeListener(this);
}

Player::~Player() {
  clear();
  device_.manager_->removeAudioCallback(&sourcePlayer_);
  sourcePlayer_.setSource(NULL);
}

void Player::setTransportState(TransportState state) {
  if (state != state()) {
    if (state == RUNNING)
      transportSource_.start();
    else
      transportSource_.stop();

    broadcastState();
  }
}

void Player::setSource(Source* source) {
  // TODO: Do we need to prepare here?
  ptr<Source>s(source);
  source_.swap(source);
  transport_.setSource(source_);
  source->releaseResources();
}

TransportState Player::state() const {
  return transport_.isPlaying() : RUNNING : STOPPED;
}

void Player::changeListenerCallback(ChangeBroadcaster*) {
  broadcastState();
}

}  // namespace slow
}  // namespace rec
