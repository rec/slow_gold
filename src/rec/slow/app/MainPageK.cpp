#include <set>

#include <glog/logging.h>

#include "MainPageJ.h"
#include "MainPageK.h"

#include "rec/audio/format/mpg123/Mpg123.h"
#include "rec/audio/AudioDeviceSetup.h"
#include "rec/slow/Preferences.h"
#include "rec/gui/RecentFiles.h"
#include "rec/data/persist/Copy.h"

#include "rec/util/STL.h"
#include "rec/util/thread/LockedMessage.h"
#include "rec/util/thread/RunnableThread.h"
#include "rec/util/thread/WaitLoop.h"
#include "rec/util/thread/Callback.h"
#include "rec/data/yaml/Yaml.h"

using namespace juce;
using namespace rec::thread;
using namespace rec::widget::tree;

using rec::audio::source::Source;
using rec::audio::source::TimeStretch;
using rec::persist::copy;
using rec::util::thread::ThreadDescription;
using rec::widget::waveform::WaveformProto;

using namespace rec::util::thread;

namespace rec {
namespace slow {

const File::SpecialLocationType MainPageK::START_DIR = File::userHomeDirectory;
const char* MainPageK::PREVIEW_THREAD_NAME = "audio file preview";
static const int CHANGE_LOCKER_WAIT = 100;

MainPageK::MainPageK(AudioDeviceManager* d)
  : deviceManager_(d),
    changeLocker_(new ChangeLocker<Preferences>(CHANGE_LOCKER_WAIT)),
    newPosition_(-1),
    samplePosition_(-1),
    transportSourceSet_(false) {
}

MainPageK::~MainPageK() {}

static Thread* makeCursorThread(MainPageK* main) {
  ThreadDescription thumbnail(slow::getPreferences().thumbnail().cursor_thread());
  Runnable* callback = makeCallback(main, &MainPageK::updateCursor);
  Runnable* locked = new LockedMessage(callback);
  Thread* t = new RunnableThread("cursor", new WaitLoop(thumbnail.period(), locked));
  t->setPriority(thumbnail.priority());
  return t;
}

void MainPageK::operator()(const Preferences& prefs) {
  const VolumeFile& file = prefs.track().file();
  if (file != prefs_.track().file()) {
    transportSource_.stop();
    transportSource_.setPosition(0);
    peer_->thumbnail->setFile(file);
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

  peer_->treeTreeComp->addListener(this);
  peer_->treeTreeComp->update();

  TimeStretch d = getPreferences().track().timestretch();

  peer_->timeScaleSlider->setValue(d.time_scale());
  peer_->pitchScaleSlider->setValue(d.pitch_scale());

  peer_->waveform->addListener(this);
  transportSource_.addChangeListener(this);
  deviceManager_->addAudioCallback(&player_);
  deviceManager_->addChangeListener(this);
  player_.setSource(&transportSource_);

  rec::audio::format::mpg123::initializeOnce();

  doubleRunny_.addListener(this);
  cursorThread_.reset(makeCursorThread(this));
  cursorThread_->startThread();

  changeLocker_->addListener(this);
  changeLocker_->startThread();
  prefs()->addListener(changeLocker_.get());
  peer_->treeTreeComp->startThread();

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
  } else {
#if 0
    DLOG(INFO) << "Creating a new audio setup file";
    deviceManager_->getAudioDeviceSetup(setup);
    audio::AudioDeviceSetupProto setupProto;
    if (false && persist::copy(setup, &setupProto))
      audioSetupData()->setter()->set(setupProto);
    else
      LOG(ERROR) << "Couldn't uncopy audio setup data";
#endif
  }
}

void MainPageK::destruct() {
  // TODO: why does this have to be called so early in the destructor sequence?
  // Can we get rid of all of this entirely?
  trash::discard(changeLocker_.transfer());
  trash::discard(cursorThread_.transfer());

  transportSource_.setSource(NULL);
  player_.setSource(NULL);

  deviceManager_->removeAudioCallback(&player_);
  deviceManager_->removeChangeListener(this);
  peer_->thumbnail->removeChangeListener(this);
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

void MainPageK::operator()(double cursorRatio) {
  DLOG(INFO) << "Setting cursor " << cursorRatio;
  return;

  ScopedLock l(changeLocker_->lock());
  {
    ScopedLock l(lock_);
    int np = (cursorRatio * transportSource_.getTotalLength()) / 44100;
    newPosition_ = np;
  }
  prefs()->requestUpdate();
}

void MainPageK::updateCursor() {
  int length = transportSource_.getTotalLength();
  double current = transportSource_.getCurrentPosition();
  int old = samplePosition_;
  samplePosition_ = RATE * current;
  if (samplePosition_ == old || !length)
    return;

  double position = samplePosition_ / (1.0 * length);
  peer_->thumbnail->setCursor(position);
  peer_->realDial->setTimeRatio(position);
  peer_->songDial->setTimeRatio(position);
  peer_->realTime->setTimeSamples(samplePosition_);

  double scale = getPreferences().track().timestretch().time_scale();
  peer_->songTime->setTimeSamples(samplePosition_ / scale);
}

void MainPageK::loadFileIntoTransport(const VolumeFile& file) {
  if (transportSource_.isPlaying())
    transportSource_.stop();
  prefs()->setter()->set("track", "file", file);
}

void MainPageK::sliderValueChanged(Slider* slider) {
  double v = slider->getValue();
  if (slider == peer_->zoomSlider)
     peer_->thumbnail->setZoomFactor(v);

  if (slider == peer_->timeScaleSlider)
    prefs()->setter()->set("track", "timestretch", "time_scale", v);

  else if (slider == peer_->pitchScaleSlider)
    prefs()->setter()->set("track", "timestretch", "pitch_scale", v);
}

static const char* const CD_STATE_NAMES[] = {
  "unknown",                /** An error condition, if the device isn't responding. */
  "trayOpen",               /** The drive is currently open. Note that a slot-loading drive
                                may seem to be permanently open. */
  "noDisc",                 /** The drive has no disk in it. */
  "Writablediskpresent",    /** The drive contains a writeable disk. */
  "readOnlyDiskPresent"     /** The drive contains a read-only disk. */
};

void MainPageK::changeListenerCallback(juce::ChangeBroadcaster* objectThatHasChanged) {
  if (objectThatHasChanged == &transportSource_)
    updateCursor();

  if (objectThatHasChanged == deviceManager_) {
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
