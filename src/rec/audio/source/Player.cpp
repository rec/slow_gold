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
    : device_(d), timer_(NULL), stretchy_(NULL), stereo_(NULL), buffered_(NULL) {
  device_->manager_.addAudioCallback(&player_);
  timer_ = new Timer();
  selection_ = new Selection(timer_);
  stretchy_ = new Stretchy(selection_);
  stretchy_->initialize();
  stereo_ = new Stereo(stretchy_);

  static const bool IS_BUFFERED = false;
  if (IS_BUFFERED)
    level_.setSource(buffered_ = new Buffered(stereo_));
  else
    level_.setSource(stereo_);

  transportSource_.setSource(&level_);
  player_.setSource(&transportSource_);
}

Player::~Player() {
  transportSource_.setSource(NULL);
}

SamplePosition Player::getNextReadPosition() {
  return selection_->getNextReadPosition();
}

void Player::setNextReadPosition(int64 t) {
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
                       const StereoProto& stereo,
                       const block::BlockSet& selection) {
  ptr<Source> s(source);

  timer_->swap(&s);
  selection_->setSelection(selection);
  stretchy_->setStretch(stretch);
  stretchy_->initialize();
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

void Player::onDataChange(const StereoProto& s) {
  stereo_->setStereo(s);
}

void Player::setSelection(const block::BlockSet& s) {
  selection_->setSelection(s);
}

void Player::onDataChange(const LoopPointList& lpl) {
  setSelection(audio::getTimeSelection(lpl, length()));
}


void Player::clearSource() {
  setSource(new Empty, Stretch(), StereoProto(), block::BlockSet());
}

void Player::onDataChange(const Gain& gain) {
  setGain(getGain(gain));
}

void Player::setGain(double gain) {
  player_.setGain(gain);
}

}  // namespace source
}  // namespace audio
}  // namespace rec
