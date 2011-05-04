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

Player::Player(Device* d) : device_(d), timer_(new Timey) {
  player_.setSource(&transportSource_);
  device_->manager_.addAudioCallback(&player_);
  transportSource_.setSource(timer_.get());
  setSource(new Empty);
}

Player::~Player() {
  timer_.transfer();
}

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
  ptr<Source> s(source);
  timer_->swap(&s);

  // TODO: Do we need to prepare here?
  if (source)
    timer_->setNextReadPosition(source->getNextReadPosition());

  if (s)
    s->releaseResources();

  s.transfer();
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
