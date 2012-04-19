#include "rec/audio/source/Player.h"
#include "rec/audio/Audio.h"
#include "rec/audio/Device.h"
#include "rec/audio/source/Empty.h"
#include "rec/audio/source/Level.h"
#include "rec/audio/source/Selection.h"
#include "rec/audio/source/Stereo.h"
#include "rec/audio/source/Timer.h"
#include "rec/audio/stretch/Stretchy.h"
#include "rec/audio/util/Gain.h"
#include "rec/util/Math.h"
#include "rec/util/block/Block.h"

namespace rec {
namespace audio {
namespace source {

using namespace rec::audio::transport;
using namespace rec::audio::stretch;

Player::Player(Device* d) : device_(d),
                            timer_(new Timer(NULL)),
                            selection_(new Selection(timer_)),
                            stretchy_(new Stretchy(selection_)),
                            stereo_(new Stereo(stretchy_)) {
  level_.setSource(stereo_);
  device_->manager_.addAudioCallback(&player_);
  transportSource_.setSource(&level_);
  player_.setSource(&transportSource_);
}

Player::~Player() {
  transportSource_.setSource(NULL);
}

void Player::init() {
  DataListener<Gain>::init();
  DataListener<LoopPointList>::init();
  DataListener<StereoProto>::init();
  DataListener<stretch::Stretch>::init();
}

Samples<44100> Player::getNextReadPosition() {
  return selection_->getNextReadPosition();
}

void Player::setNextReadPosition(const Samples<44100>& time) {
  selection_->setNextReadPosition(time);
}

void Player::broadcastState() {
  level_.clear();
  broadcast(state());
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

void Player::operator()(const stretch::Stretch& stretch) {
  level_.clear();
  stretchy_->setStretch(stretch);
}

void Player::operator()(const StereoProto& s) {
  stereo_->setStereo(s);
}

void Player::operator()(const LoopPointList& loops) {
  selection_->setSelection(getTimeSelection(loops));
}

void Player::operator()(const Gain& gain) {
  setGain(getGain(gain));
}

void Player::reset() {
  setState(audio::transport::STOPPED);
  timer_->setNextReadPosition(0);
}

State Player::state() const {
  return transportSource_.isPlaying() ? RUNNING : STOPPED;
}

void Player::changeListenerCallback(ChangeBroadcaster*) {
  broadcastState();
}

void Player::setGain(double gain) {
  player_.setGain(static_cast<float>(gain));
}

Source* Player::makeSourceCopy(Source* s, bool useSelection) {
  Lock l(lock_);
  ptr<Source> source(s);
  if (useSelection) {
    ptr<Selection> selection(new Selection(source.transfer()));
    selection->setSelection(selection_->selection());
    source.reset(selection.transfer());
  }

  ptr<Stretchy> stretchy(new Stretchy(source.transfer()));
  stretchy->setStretch(stretchy_->getStretch());
  source.reset(stretchy.transfer());

  // TODO: we don't take into account the final "gain" slider.
  return source.transfer();
}

}  // namespace source
}  // namespace audio
}  // namespace rec
