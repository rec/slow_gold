#include "rec/audio/source/Player.h"
#include "rec/audio/source/BufferSource.h"
#include "rec/audio/source/Empty.h"
#include "rec/audio/source/Timey.h"
#include "rec/audio/Audio.h"
#include "rec/audio/Device.h"
#include "rec/util/Math.h"

namespace rec {
namespace audio {
namespace source {

using namespace rec::audio::transport;

Player::Player(Device* d) : device_(d) {
  player_.setSource(&transportSource_);
  device_->manager_.addAudioCallback(&player_);
  setSource(new Empty);
}

Player::~Player() {}

void Player::setState(State s) {
  if (s != state()) {
    if (s == transport::RUNNING)
      transportSource_.start();
    else
      transportSource_.stop();

    broadcastState();
  }
}

void Player::setSource(Source* source) {
  Timey* timey = source ? new Timey(source) : NULL;
  timeBroadcaster_ = timey;

  // TODO: Do we need to prepare here?
  ptr<Source> s(timey);
  source_.swap(s);
  transportSource_.setSource(source_.get());  // TODO
  if (s)
    s->releaseResources();
}

State Player::state() const {
  return transportSource_.isPlaying() ? RUNNING : STOPPED;
}

void Player::changeListenerCallback(ChangeBroadcaster*) {
  broadcastState();
}

}  // namespace source
}  // namespace audio
}  // namespace rec
