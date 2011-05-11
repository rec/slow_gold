#include "rec/audio/source/Player.h"
#include "rec/audio/Audio.h"
#include "rec/audio/Device.h"
#include "rec/audio/source/BufferSource.h"
#include "rec/audio/source/Buffered.h"
#include "rec/audio/source/Empty.h"
#include "rec/audio/source/Selection.h"
#include "rec/audio/source/Stereo.h"
#include "rec/audio/source/Timer.h"
#include "rec/util/Math.h"

namespace rec {
namespace audio {
namespace source {

using namespace rec::audio::transport;

Player::Player(Device* d) : device_(d) {
  player_.setSource(&transportSource_);
  device_->manager_.addAudioCallback(&player_);
  timer_ = new Timer;
  selection_ = new Selection(timer_);
  stereo_ = new Stereo(selection_);
  buffered_ = new Buffered(stereo_, BUFFER_SIZE);
  source_.reset(buffered_);

  transportSource_.setSource(source_.get());

  setSource(new Empty);
}

Player::~Player() {
  transportSource_.setSource(NULL);
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

#if 0
  if (source)  // TODO: is this even needed
    timer_->setNextReadPosition(source->getNextReadPosition());
#endif

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

void Player::setStereoProto(const StereoProto& s) {
  stereo_->setStereo(s);
}

void Player::setSelection(const block::BlockSet& s) {
  selection_->setSelection(s);
}

}  // namespace source
}  // namespace audio
}  // namespace rec
