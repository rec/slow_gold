#include <set>

#include <glog/logging.h>

#include "rec/slow/Preferences.pb.h"

#include "MainPageJ.h"
#include "MainPageK.h"

#include "AudioThumbnailComponent.h"
#include "rec/audio/format/mpg123/Mpg123.h"
#include "rec/slow/Preferences.h"
#include "rec/persist/Copy.h"
#include "rec/util/Proto.h"

#include "rec/thread/LockedMessage.h"
#include "rec/thread/RunnableThread.h"
#include "rec/thread/WaitLoop.h"
#include "rec/thread/Callback.h"

using rec::audio::timescaler::TimeStretch;
using rec::gui::ThumbnailDescription;
using rec::persist::copy;

// TODO: why can't this be defined in the .h with other primitives?!

namespace rec {
namespace slow {

const TreeView::ColourIds MainPageK::BACKGROUND = FileTreeComponent::backgroundColourId;
const Colour MainPageK::FOREGROUND = Colours::white;
const File::SpecialLocationType MainPageK::START_DIR = File::userHomeDirectory;
const char* MainPageK::PREVIEW_THREAD_NAME = "audio file preview";

MainPageK::MainPageK(AudioDeviceManager* d)
  : deviceManager_(d),
    directoryListThread_(PREVIEW_THREAD_NAME),
    directoryList_(NULL, directoryListThread_),
    cdNames_(AudioCDBurner::findAvailableDevices()) {
}

using rec::gui::ThreadDescription;
using rec::gui::ThumbnailDescription;
using rec::thread::Callback;
using rec::thread::LockedMessage;
using rec::thread::Runnable;
using rec::thread::RunnableThread;
using rec::thread::WaitLoop;
using rec::thread::makeCallback;

static Thread* makeCursorThread(MainPageK* main) {
  ThreadDescription thumbnail(slow::getThumbnail().cursor_thread());
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

  peer_->fileTreeComp->setColour(BACKGROUND, FOREGROUND);
  peer_->fileTreeComp->addListener(this);

  TimeStretch d = getPreferences().loop_window(0).timestretch();

  peer_->timeScaleSlider->setValue(d.time_scale());
  peer_->pitchScaleSlider->setValue(d.pitch_scale());

  burners_.resize(cdNames_.size());
  for (int i = 0; i < burners_.size(); ++i) {
    burners_[i] = AudioCDBurner::openDevice(i);
    burners_[i]->addChangeListener(this);
    changeListenerCallback(burners_[i]);
  }

  transportSource_.addChangeListener(this);
  deviceManager_->addAudioCallback(&player_);
  player_.setSource(&transportSource_);
  rec::audio::format::mpg123::initializeOnce();

  cursorThread_.reset(makeCursorThread(this));
  cursorThread_->startThread();

  Preferences prefs(getPreferences());
  if (prefs.has_recent_files()) {
    const RecentFiles& recent = prefs.recent_files();
    if (int size = recent.name_size()) {
      if (recent.reload_most_recent())
        loadFileIntoTransport(File(copy(recent.name(size - 1))));
    }
  }
}

void MainPageK::destruct() {
  // TODO: why does this have to be called so early in the destructor sequence?
  // Can we get rid of all of this entirely?
  cursorThread_->signalThreadShouldExit();
  transportSource_.setSource(NULL);
  player_.setSource(NULL);

  deviceManager_->removeAudioCallback(&player_);
  peer_->fileTreeComp->removeListener(this);

  for (int i = 0; i < burners_.size(); ++i)
    delete burners_[i];

  burners_.clear();
}

void MainPageK::loadRecentFile(int menuItemID) {
  RecentFiles recent = getPreferences().recent_files();
  loadFileIntoTransport(copy(recent.name(menuItemID - 1)));
}

void MainPageK::updateCursor() {
  double position = transportSource_.getCurrentPosition();
  peer_->thumbnail->setCursor(position);
}

void MainPageK::setPosition(double position) {
  transportSource_.setPosition(position);
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

    TimeStretch d = getPreferences().loop_window(0).timestretch();
    AudioFormatReaderSource *s0 = new AudioFormatReaderSource(r0, true);
    AudioFormatReaderSource *s1 = new AudioFormatReaderSource(r1, true);

    stretchyDeleter_.reset(new DoubleStretchyThread(d, s0, s1));
    stretchyDeleter_.swap(stretchy_);

    loopingButtonClicked();
    transportSource_.setSource(stretchy_.get());

    LockedPreferences prefs;
    RecentFiles* recent = prefs->mutable_recent_files();
    rec::proto::addOrMoveToEnd(copy(file.getFullPathName()),
                               recent->mutable_name());
    rec::proto::truncateTo(recent->max_files(),
                           recent->mutable_name(), std::string());

    peer_->thumbnail->setFile(file);
  } else {
    LOG(ERROR) << "Didn't understand file type for filename "
               << file.getFullPathName();
  }
}

void MainPageK::sliderValueChanged(Slider* slider) {
  if (slider == peer_->zoomSlider) {
    peer_->thumbnail->setZoomFactor(slider->getValue());
    return;
  }

  {
    LockedPreferences prefs;
    TimeStretch* stretch = prefs->mutable_loop_window(0)->mutable_timestretch();
    if (slider == peer_->timeScaleSlider)
      stretch->set_time_scale(slider->getValue());

    else if (slider == peer_->pitchScaleSlider)
     stretch->set_pitch_scale(slider->getValue());

    else
      return;

    if (stretchy_)
      stretchy_->setDescription(*stretch);
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
  if (objectThatHasChanged == &transportSource_) {
    double position = transportSource_.getCurrentPosition();
    peer_->thumbnail->setCursor(position);
    return;
  }

  AudioCDBurner* cd = (AudioCDBurner*) objectThatHasChanged;
  AudioCDBurner::DiskState state = cd->getDiskState();
  LOG(INFO) << CD_STATE_NAMES[state];

  if (state != AudioCDBurner::readOnlyDiskPresent)
    return;

  int i = 0;
  for (; i < burners_.size() && burners_[i] != cd; ++i);
  if (i == burners_.size())
    return;

  scoped_ptr<AudioCDReader> reader(AudioCDReader::createReaderForCD(i));
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

void MainPageK::selectionChanged() {
  peer_->zoomSlider->setValue(0, false, false);

  File file = peer_->fileTreeComp->getSelectedFile();
  loadFileIntoTransport(file);
}

}  // namespace slow
}  // namespace rec
