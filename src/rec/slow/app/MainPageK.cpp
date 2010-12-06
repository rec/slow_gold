#include <set>

#include <glog/logging.h>

#include "MainPageJ.h"
#include "MainPageK.h"

#include "rec/audio/format/mpg123/Mpg123.h"
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
using rec::util::thread::ChangeLocker;
using rec::widget::AudioThumbnailDesc;
using namespace rec::util::thread;

namespace rec {
namespace slow {

const File::SpecialLocationType MainPageK::START_DIR = File::userHomeDirectory;
const char* MainPageK::PREVIEW_THREAD_NAME = "audio file preview";
static const int CHANGE_LOCKER_WAIT = 100;

MainPageK::MainPageK(AudioDeviceManager* d)
  : directoryListThread_(PREVIEW_THREAD_NAME),
    deviceManager_(d),
    changeLocker_(new ChangeLocker<slow::proto::Preferences>(CHANGE_LOCKER_WAIT)),
    newPosition_(-1) {
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
  int newPosition = -1;
  {
    ScopedLock l(changeLocker_->lock());
    if (newPosition_ != -1) {
      newPosition = newPosition_;
      newPosition_ = -1;
    }
  }

  if (prefs.track().file() != prefs_.track().file()) {
    if (transportSource_.isPlaying())
      transportSource_.stop();
    transportSource_.setPosition(0);
    peer_->thumbnail->setFile(prefs.track().file());

  } else if (prefs.track() == prefs_.track() && newPosition == -1) {
    return;
  }

  Thread* thread = Thread::getCurrentThread();
  scoped_ptr<Runny> runny(newRunny(prefs_.track()));

  if (runny) {
    static const int SAMPLES = 0;
    runny->setNextReadPosition((newPosition == -1) ?
                               transportSource_.getCurrentPosition() + SAMPLES :
                               newPosition);
    while (!thread->threadShouldExit() && !runny->fill());
    runny->startThread();
    runny.swap(runny_);
    transportSource_.setSource(runny_.get());
    if (newPosition != -1)
      transportSource_.setPosition(newPosition);

    trash::discard(runny.transfer());
  }
  prefs_ = prefs;
}

void MainPageK::construct(MainPageJ* peer) {
  peer_ = peer;

  directoryListThread_.startThread(THREAD_PRIORITY);

  peer_->treeTreeComp->addListener(this);
  peer_->treeTreeComp->update();

  TimeStretch d = getPreferences().track().timestretch();

  peer_->timeScaleSlider->setValue(d.time_scale());
  peer_->pitchScaleSlider->setValue(d.pitch_scale());

  peer_->thumbnail->addChangeListener(this);

  transportSource_.addChangeListener(this);
  deviceManager_->addAudioCallback(&player_);
  player_.setSource(&transportSource_);

  rec::audio::format::mpg123::initializeOnce();

  cursorThread_.reset(makeCursorThread(this));
  cursorThread_->startThread();

  changeLocker_->addListener(this);
  changeLocker_->startThread();
  prefs()->addListener(changeLocker_.get());
  prefs()->requestUpdate();
}

void MainPageK::destruct() {
  // TODO: why does this have to be called so early in the destructor sequence?
  // Can we get rid of all of this entirely?
  trash::discard(changeLocker_.transfer());
  trash::discard(cursorThread_.transfer());
  trash::discard(runny_.transfer());

  transportSource_.setSource(NULL);
  player_.setSource(NULL);

  deviceManager_->removeAudioCallback(&player_);
  peer_->thumbnail->removeChangeListener(this);
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

void MainPageK::updateCursor() {
  int length = transportSource_.getTotalLength();
  if (!length)
    return;
  double samples = RATE * transportSource_.getCurrentPosition();
  double position = samples / length;
  peer_->thumbnail->setCursor(position);
  peer_->realDial->setTimeRatio(position);
  peer_->songDial->setTimeRatio(position);
  peer_->realTime->setTimeSamples(samples);
  double scale = getPreferences().track().timestretch().time_scale();
  peer_->songTime->setTimeSamples(samples / scale);
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
  if (objectThatHasChanged == &transportSource_) {
    updateCursor();
  }

  if (objectThatHasChanged == peer_->thumbnail) {
    ScopedLock l(changeLocker_->lock());

    double ratio = peer_->thumbnail->ratio();
    newPosition_ = (ratio * transportSource_.getTotalLength()) / RATE;
    prefs()->requestUpdate();
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

void MainPageK::loopingButtonClicked() {
}

void MainPageK::cut() {
  proto::Preferences prefs = slow::getPreferences();
  string s = yaml::write(prefs);
  SystemClipboard::copyTextToClipboard(s.c_str());
  LOG(INFO) << s;
}

void MainPageK::paste() {
  string s = SystemClipboard::getTextFromClipboard().toCString();
  LOG(INFO) << s;
  proto::Preferences prefs;
  yaml::read(s, &prefs);
}

}  // namespace slow
}  // namespace rec
