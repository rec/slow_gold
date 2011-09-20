#include "rec/audio/source/Player.h"
#include "rec/audio/Audio.h"
#include "rec/audio/Device.h"
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
  : device_(d),
    timer_(new Timer()),
    selection_(new Selection(timer_)),
    stretchy_(new Stretchy(selection_)),
    stereo_(new Stereo(stretchy_)) {
  stretchy_->initialize();
  level_.setSource(stereo_);
  device_->manager_.addAudioCallback(&player_);

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

void Player::setSource(Source* source) {
  timer_->setSource(source);
}

void Player::setStretch(const Stretch& stretch) {
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
  if (lpl.loop_point_size() < 2)
    DLOG(INFO) << "empty LoopPointList " << lpl.loop_point_size();
  else
    setSelection(audio::getTimeSelection(lpl));
}

void Player::clear() {
  setState(audio::transport::STOPPED);
  timer_->setNextReadPosition(0);
}

void Player::onDataChange(const Gain& gain) {
  setGain(getGain(gain));
}

void Player::setGain(double gain) {
  player_.setGain(static_cast<float>(gain));
}

}  // namespace source
}  // namespace audio
}  // namespace rec
