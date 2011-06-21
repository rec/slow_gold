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
#include "rec/audio/util/Gain.h"
#include "rec/util/Math.h"

namespace rec {
namespace audio {
namespace source {

using namespace rec::audio::transport;
using namespace rec::audio::stretch;

Player::Player(Device* d)
    : device_(d), stretchy_(NULL), stereo_(NULL), buffered_(NULL) {
  device_->manager_.addAudioCallback(&player_);
  selection_ = new Selection(new Empty());
  stretchy_ = new Stretchy(selection_);
  stereo_ = new Stereo(selection_);
  // buffered_ = new Buffered(stereo_);
  timer_ = new Timer(stereo_); // buffered_);
  level_ = new Level(timer_);
  source_.reset(level_);

  transportSource_.setSource(source_.get());
  player_.setSource(&transportSource_);

  // clearSource();
}

Player::~Player() {
  transportSource_.setSource(NULL);
}

SamplePosition Player::getNextReadPosition() {
  return selection_->getNextReadPosition();
}

void Player::setNextReadPosition(SamplePosition t) {
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

void Player::setSource(Source* source, const Stretch& stretch,
                       const block::BlockSet& selection) {
  selection_ = new Selection(source);
  selection_->setSelection(selection);
  stretchy_ = new Stretchy(selection_);
  stretchy_->setStretch(stretch);
  ptr<Source> trash(stretchy_);
  stereo_->swap(&trash);

  if (trash)
    trash->releaseResources();
  // trash.transfer();  TODO
}

void Player::setStretch(const Stretch& stretch) {
  if (stretchy_)
    stretchy_->setStretch(stretch);
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
  setSource(new Empty, Stretch(), block::BlockSet());
}

void Player::setGain(const Gain& gain) {
  setGain(getGain(gain));
}

void Player::setGain(double gain) {
  player_.setGain(gain);
}

}  // namespace source
}  // namespace audio
}  // namespace rec
