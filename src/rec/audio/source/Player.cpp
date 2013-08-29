#include "rec/audio/source/Player.h"
#include "rec/audio/source/Empty.h"
#include "rec/audio/stretch/Implementation.h"
#include "rec/util/Math.h"

namespace rec {
namespace audio {
namespace source {

using namespace rec::audio;
using namespace rec::audio::stretch;
using namespace rec::audio::transport;
using namespace rec::widget::waveform;

Player::Player(Device* d) : device_(d) {}

void Player::init() {
  doLog("Player::init");
  doLog("Timer::init");
  timer_ = new Timer(nullptr);
  doLog("Selection::init");
  selection_ = new Selection(timer_);
  doLog("Stretchy::Stretchy");
  stretchy_ = new Stretchy(selection_);
  doLog("Stretchy::init");
  stretchy_->init(device_->getSampleRate());
  doLog("Stereo::init");
  stereo_ = new Stereo(stretchy_);
  doLog("level setting");
  level_.setSource(stereo_);
  doLog("adding callback");
  device_->manager_.addAudioCallback(&player_);
  doLog("Setting source");
  transportSource_.setSource(&level_);
  doLog("setting transport source");
  player_.setSource(&transportSource_);
}


Player::~Player() {
  transportSource_.setSource(nullptr);
}

SampleTime Player::getNextReadPosition() {
  return selection_->getNextReadPosition();
}

void Player::setNextReadPosition(const SampleTime& time) {
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

void Player::setInputSampleRate(SampleRate rate) {
  stretchy_->implementation()->setInputSampleRate(rate);
}

void Player::operator()(const AudioSettings& settings) {
  stretchy_->implementation()->setMasterTune(settings.master_tune());
}

void Player::operator()(const StereoProto& s) {
  stereo_->setStereo(s);
}

void Player::operator()(SampleRate sampleRate) {
  stretchy_->implementation()->setOutputSampleRate(sampleRate);
}

void Player::operator()(const Stretch& stretch) {
  level_.clear();
  stretchy_->implementation()->setStretch(stretch);
}

void Player::operator()(const Viewport& viewport) {
  selection_->setSelection(getTimeSelection(viewport.loop_points()));
  if (viewport.loop_points().has_sample_rate())
    setInputSampleRate(viewport.loop_points().sample_rate());
}

SampleTime Player::getSelectionLength() const {
  double s = stretchy_->implementation()->timeScale();
  return static_cast<int64>(s * selection_->getCorrectTotalLength());
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
    ptr<Selection> selection(new Selection(source.release()));
    selection->setSelection(selection_->selection());
    source.reset(selection.release());
  }

  ptr<Stretchy> stretchy(new Stretchy(source.release(), *stretchy_));
  source.reset(stretchy.release());
  return source.release();
}

}  // namespace source
}  // namespace audio
}  // namespace rec
