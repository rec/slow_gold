#include <set>

#include <glog/logging.h>

#include "MainPageJ.h"
#include "MainPageK.h"

#include "rec/audio/format/mpg123/Mpg123.h"
#include "rec/slow/Preferences.h"
#include "rec/gui/RecentFiles.h"
#include "rec/data/persist/Copy.h"

#include "rec/util/thread/LockedMessage.h"
#include "rec/util/thread/RunnableThread.h"
#include "rec/util/thread/WaitLoop.h"
#include "rec/util/thread/Callback.h"
#include "rec/data/yaml/Yaml.h"

using rec::audio::source::TimeStretch;

using rec::widget::ThreadDescription;
using rec::widget::AudioThumbnailDesc;

using rec::persist::copy;

using rec::thread::Callback;
using rec::thread::LockedMessage;
using rec::thread::Runnable;
using rec::thread::RunnableThread;
using rec::thread::WaitLoop;
using rec::thread::makeCallback;

using namespace juce;
using namespace rec::widget::tree;

namespace rec {
namespace slow {

const File::SpecialLocationType MainPageK::START_DIR = File::userHomeDirectory;
const char* MainPageK::PREVIEW_THREAD_NAME = "audio file preview";

MainPageK::MainPageK(AudioDeviceManager* d)
  : directoryListThread_(PREVIEW_THREAD_NAME),
    directoryList_(NULL, directoryListThread_),
    deviceManager_(d) {
}

static Thread* makeCursorThread(MainPageK* main) {
  ThreadDescription thumbnail(slow::getPreferences().thumbnail().cursor_thread());
  Runnable* callback = makeCallback(main, &MainPageK::updateCursor);
  Runnable* locked = new LockedMessage(callback);
  Thread* t = new RunnableThread("cursor", new WaitLoop(thumbnail.period(), locked));
  t->setPriority(thumbnail.priority());
  return t;
}

void MainPageK::construct(MainPageJ* peer) {
  peer_ = peer;

  directoryList_.setDirectory(File::getSpecialLocation(START_DIR), true, true);
  directoryListThread_.startThread(THREAD_PRIORITY);

  peer_->treeTreeComp->listeners()->insert(this);
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

  gui::RecentFiles recent = gui::getSortedRecentFiles();
  if (recent.reload_most_recent() && recent.file_size())
    loadRecentFile(1);
}

void MainPageK::destruct() {
  // TODO: why does this have to be called so early in the destructor sequence?
  // Can we get rid of all of this entirely?
  cursorThread_->signalThreadShouldExit();
  transportSource_.setSource(NULL);
  player_.setSource(NULL);

  deviceManager_->removeAudioCallback(&player_);
  peer_->thumbnail->removeChangeListener(this);
}

void MainPageK::loadRecentFile(int menuItemID) {
  gui::RecentFiles recent = gui::getSortedRecentFiles();
  loadFileIntoTransport(File(recent.file(menuItemID - 1).name().c_str()));
}

// TODO: fix this magic constant
static const int RATE = 44100;

void MainPageK::operator()(const VolumeFile& file) {
  if (file.volume().type() == Volume::CD)
    LOG(ERROR) << "Couldn't open CD file " << file.DebugString();
  else
    loadFileIntoTransport(getFile(file));
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

void MainPageK::loadFileIntoTransport(const File& file) {
  AudioFormatManager* afm = AudioFormatManager::getInstance();
  if (AudioFormatReader* r0 = afm->createReaderFor(file)) {
    AudioFormatReader* r1 = afm->createReaderFor(file);
    DCHECK(r1);

    transportSource_.stop();
    transportSource_.setSource(NULL);
    if (stretchy_)
      stretchy_->stop();

    TimeStretch d = getPreferences().track().timestretch();
    AudioFormatReaderSource *s0 = new AudioFormatReaderSource(r0, true);
    AudioFormatReaderSource *s1 = new AudioFormatReaderSource(r1, true);

    stretchyDeleter_.reset(new DoubleStretchyThread(s0, s1));
    stretchyDeleter_.swap(stretchy_);
    stretchy_->setDescription(d);

    loopingButtonClicked();
    transportSource_.setSource(stretchy_.get());

    gui::addRecentFile(file.getFullPathName().toCString());

    peer_->thumbnail->setFile(file);
  } else {
    LOG(ERROR) << "Didn't understand file type for filename "
               << file.getFullPathName();
  }
}

void MainPageK::sliderDragEnded(Slider* slider) {
  double v = slider->getValue();
  if (slider == peer_->timeScaleSlider)
    prefs()->setter()->set("track", "timestretch", "time_scale", v);

  else if (slider == peer_->pitchScaleSlider)
    prefs()->setter()->set("track", "timestretch", "pitch_scale", v);
}

void MainPageK::sliderValueChanged(Slider* slider) {
  if (slider == peer_->zoomSlider) {
    peer_->thumbnail->setZoomFactor(slider->getValue());
    return;
  }

  if (stretchy_) {
    TimeStretch stretch = getPreferences().track().timestretch();

    if (slider == peer_->timeScaleSlider)
      stretch.set_time_scale(slider->getValue());

    else if (slider == peer_->pitchScaleSlider)
      stretch.set_pitch_scale(slider->getValue());

    else
      return;

    stretchy_->setDescription(stretch);
  }
}

static const char* const CD_STATE_NAMES[] = {
  "unknown",                /** An error condition, if the device isn't responding. */
  "trayOpen",               /** The drive is currently open. Note that a slot-loading drive
                                may seem to be permanently open. */
  "noDisc",                 /** The drive has no disk in it. */
  "Writablediskpresent",    /** The drive contains a writeable disk. */
  "readOnlyDiskPresent"     /** The drive contains a read-only disk. */
};

void MainPageK::changeListenerCallback(void* objectThatHasChanged) {
  if (objectThatHasChanged == (void*)&transportSource_) {
    updateCursor();
    return;
  }

  if (objectThatHasChanged == peer_->thumbnail) {
    double p = peer_->thumbnail->ratio();
    transportSource_.setPosition(p * transportSource_.getTotalLength() / RATE);
    return;
  }
}

void MainPageK::startStopButtonClicked() {
  if (transportSource_.isPlaying())
    transportSource_.stop();
  else
    transportSource_.start();
}

void MainPageK::loopingButtonClicked() {
  if (stretchy_)
    stretchy_->setLooping(peer_->loopingButton->getToggleState());
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
