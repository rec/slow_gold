#include <set>

#include <glog/logging.h>

#include "rec/slow/MainPageK.h"

#include "rec/audio/AudioDeviceSetup.h"
#include "rec/audio/format/mpg123/Mpg123.h"
#include "rec/data/persist/Copy.h"
#include "rec/data/yaml/Yaml.h"
#include "rec/gui/RecentFiles.h"
#include "rec/slow/MainPageJ.h"
#include "rec/slow/Preferences.h"
#include "rec/util/STL.h"
#include "rec/util/thread/Trash.h"

using namespace rec::widget::tree;

using audio::source::Source;
using audio::source::TimeStretch;
using persist::copy;
using util::thread::ThreadDescription;
using widget::waveform::WaveformProto;

namespace rec {
namespace slow {

static const char* PREVIEW_THREAD_NAME = "audio file preview";
static const int CHANGE_LOCKER_WAIT = 100;

MainPageK::MainPageK(AudioDeviceManager* d)
  : deviceManager_(d),
    changeLocker_(new ChangeLocker<Preferences>(CHANGE_LOCKER_WAIT)),
    transportSourceSet_(false) {
}

MainPageK::~MainPageK() {}

void MainPageK::operator()(const Preferences& prefs) {
  const VolumeFile& file = prefs.track().file();
  if (file != prefs_.track().file()) {
    transportSource_.stop();
    transportSource_.setPosition(0);
    peer_->thumbnail_->setFile(file);
  }

  int newPosition;
  double ratio;
  {
    ScopedLock l(lock_);
    if (prefs.track() == prefs_.track() && newPosition == -1)
      return;

    newPosition = newPosition_;
    if (newPosition == -1)
      newPosition = transportSource_.getCurrentPosition();
    ratio = prefs.track().timestretch().time_scale() /
      prefs_.track().timestretch().time_scale();
    prefs_ = prefs;
  }

  doubleRunny_.setPreferences(prefs, newPosition, ratio);
}

void MainPageK::construct(MainPageJ* peer) {
  peer_ = peer;
  deviceManager_->initialise(0, 2, 0, true, String::empty, 0);

  peer_->treeTreeComp_->addListener(this);
  peer_->treeTreeComp_->update();

  TimeStretch d = getPreferences().track().timestretch();

  peer_->timeScaleSlider_->setValue(d.time_scale());
  peer_->pitchScaleSlider_->setValue(d.pitch_scale());

  peer_->waveform_->addListener(this);
  transportSource_.addChangeListener();
  deviceManager_->addAudioCallback(&player_);
  deviceManager_->addChangeListener(this);
  player_.setSource(&transportSource_);

  rec::audio::format::mpg123::initializeOnce();

  doubleRunny_.addListener(this);
  changeLocker_->addListener(this);
  changeLocker_->startThread();
  prefs()->addListener(changeLocker_.get());
  peer_->treeTreeComp_->startThread();

  AudioDeviceSetup setup;
  if (audioSetupData()->fileReadSuccess()) {
    if (!persist::copy(audioSetupData()->get(), &setup)) {
      LOG(ERROR) << "Couldn't copy audio setup data";
    } else {
      String err = deviceManager_->setAudioDeviceSetup(setup, true);
      if (err.length())
        LOG(ERROR) << "Couldn't setAudioDeviceSetup, error " << err;
      else
        DLOG(INFO) << "read audio setup from file";
    }
  }
}

void MainPageK::destruct() {
  // TODO: why does this have to be called so early in the destructor sequence?
  // Can we get rid of all of this entirely?
  trash::discard(changeLocker_.transfer());

  transportSource_.setSource(NULL);
  player_.setSource(NULL);

  deviceManager_->removeAudioCallback(&player_);
  deviceManager_->removeChangeListener(this);
  peer_->thumbnail_->removeChangeListener(this);
}

void MainPageK::operator()(PositionableAudioSource* source) {
  // DLOG(INFO) << "New source " << newPosition_;
  bool transportSourceSet;
  int newPosition;
  {
    ScopedLock l(lock_);
    transportSourceSet = transportSourceSet_;
    transportSourceSet_ = true;
    newPosition = newPosition_;
    newPosition_ = -1;
  }

  if (!transportSourceSet) {
    transportSource_.setSource(source);
    transportSource_.setPosition(0);
  }

  if (newPosition != -1) {
    DLOG(INFO) << "Setting newPosition " << newPosition;
    transportSource_.setPosition(newPosition);
  }
}

void MainPageK::loadRecentFile(int menuItemID) {
  gui::RecentFiles recent = gui::getSortedRecentFiles();
  loadFileIntoTransport(recent.file(menuItemID - 1).file());
}

// TODO: fix this magic constant
static const int RATE = 44100;

void MainPageK::operator()(const VolumeFile& file) {
  loadFileIntoTransport(file);
}

void MainPageK::operator()(float time) {
  DLOG(INFO) << "Setting cursor " << time;
  return;

  ScopedLock l(changeLocker_->lock());
  {
    ScopedLock l(lock_);
    int np = (cursorRatio * transportSource_.getTotalLength()) / 44100;
    newPosition_ = np;
  }
  prefs()->requestUpdate();
}

void MainPageK::loadFileIntoTransport(const VolumeFile& file) {
  if (transportSource_.isPlaying())
    transportSource_.stop();
  prefs()->setter()->set("track", "file", file);
}

void MainPageK::sliderValueChanged(Slider* slider) {
  double v = slider->getValue();
  if (slider == &peer_->timeScaleSlider_)
    prefs()->setter()->set("track", "timestretch", "time_scale", v);

  if (slider == &peer_->pitchScaleSlider_)
    prefs()->setter()->set("track", "timestretch", "pitch_scale", v);
}

void MainPageK::changeListenerCallback(juce::ChangeBroadcaster* obj) {
  if (obj == deviceManager_) {
    AudioDeviceSetup setup;
    deviceManager_->getAudioDeviceSetup(setup);

    audio::AudioDeviceSetupProto setupProto;
    if (!persist::copy(setup, &setupProto)) {
      LOG(ERROR) << "Unable to copy AudioDeviceSetupProto";
      return;
    }

    DLOG(INFO) << "Audio setup changed";
    slow::audioSetupData()->setter()->set(setupProto);
  }
}

void MainPageK::startStopButtonClicked() {
  start(!transportSource_.isPlaying());
}

void MainPageK::start(bool isStart) {
  if (isStart)
    transportSource_.start();
  else
    transportSource_.stop();
}

void MainPageK::cut() {
  proto::Preferences prefs = slow::getPreferences();
  string s = yaml::write(prefs);
  SystemClipboard::copyTextToClipboard(s.c_str());
  DLOG(INFO) << s;
}

void MainPageK::paste() {
  string s = SystemClipboard::getTextFromClipboard().toCString();
  DLOG(INFO) << s;
  proto::Preferences prefs;
  yaml::read(s, &prefs);
}

}  // namespace slow
}  // namespace rec
