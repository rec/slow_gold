#include "rec/audio/source/Player.h"
#include "rec/audio/Audio.h"
#include "rec/audio/Device.h"
#include "rec/util/Math.h"

namespace rec {
namespace audio {
namespace source {

using namespace rec::audio::transport;

static const double MINIMUM_BROADCAST_TIMECHANGE = 0.001;
static const float SAMPLE_RATE = 44100.0f;

Player::Player(Device* d) : device_(d) {}

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
	DCHECK(false);
  // TODO: Do we need to prepare here?
  ptr<Source>s(source);
  source_.swap(s);
  // transportSource_.setSource(source_);  // TODO
  source->releaseResources();
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
