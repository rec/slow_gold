#include "rec/audio/source/Player.h"
#include "rec/audio/Audio.h"
#include "rec/audio/Device.h"
#include "rec/audio/source/BufferSource.h"
#include "rec/audio/source/Buffered.h"
#include "rec/audio/source/Empty.h"
#include "rec/audio/source/Level.h"
#include "rec/audio/source/Selection.h"
#include "rec/audio/source/Stereo.h"
#include "rec/audio/source/Timer.h"
#include "rec/audio/source/Stretchy.h"
#include "rec/util/Math.h"

namespace rec {
namespace audio {
namespace source {

using namespace rec::audio::transport;
using namespace rec::audio::stretch;

Player::Player(Device* d)
    : device_(d), stretchy_(NULL), stereo_(NULL), buffered_(NULL) {
  player_.setSource(&transportSource_);
  device_->manager_.addAudioCallback(&player_);
  timer_ = new Timer;
  selection_ = new Selection(timer_);
  stretchy_ = new Stretchy(selection_);
  stereo_ = new Stereo(stretchy_);
  level_ = new Level(stereo_);
  buffered_ = new Buffered(level_, BUFFER_SIZE);
  source_.reset(buffered_);

  transportSource_.setSource(source_.get());

  clearSource();
}

 Player::~Player() {
  transportSource_.setSource(NULL);
}

SampleTime Player::getNextReadPosition() {
  return selection_->getNextReadPosition();
}

void Player::setNextReadPosition(SampleTime t) {
  selection_->setNextReadPosition(t);
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

void Player::setSource(Source* source, const stretch::Stretch& stretch) {
  ptr<Source> s(source);
  timer_->swap(&s);

  static const double DELTA = 0.00001;
  double timeRatio = timeScale(stretch);
  if (stretch.passthrough_when_disabled() &&
      near(timeRatio, 1.0, DELTA) &&
      near(stretch::pitchScale(stretch), 1.0, DELTA)) {
  } else {

  }


#if 0
  if (source)  // TODO: is this even needed
    timer_->setNextReadPosition(source->getNextReadPosition());
#endif

  if (s)
    s->releaseResources();

  s.transfer();
}

void Player::setStretch(const Stretch& stretch) {
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

void Player::clearSource() {
  setSource(new Empty, Stretch());
}


}  // namespace source
}  // namespace audio
}  // namespace rec
