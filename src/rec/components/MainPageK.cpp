#include <glog/logging.h>

#include "MainPageJ.h"
#include "MainPageK.h"

#include "AudioThumbnailComponent.h"
#include "rec/audio/Math.h"
#include "JuceLibraryCode/JuceHeader.h"
#include "rec/audio/format/mpg123/Mpg123.h"
#include "rec/slow/Preferences.h"

using rec::audio::timescaler::Description;
using rec::persist::Data;

// TODO: why can't this be defined in the .h with other primitives?!

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

namespace {

class CursorThread : public Thread {
 public:
  static const int INTERVAL = 5;
  explicit CursorThread(MainPageK* main) : Thread("cursor"), main_(main) {
    setPriority(6);
  }

  void run() {
    while (!threadShouldExit()) {
      {
        MessageManagerLock lock(this);
        if (!lock.lockWasGained())
          return;
        main_->updateCursor();
      }
      wait(INTERVAL);
    }
  }

 private:
  MainPageK* main_;
  DISALLOW_COPY_ASSIGN_AND_EMPTY(CursorThread);
};

}

void MainPageK::construct(MainPageJ* peer) {
  {
    Data<rec::slow::Preferences>::Access access(rec::slow::getPreferences());
    access->mutable_thumbnail()->mutable_background()->set_rgb(0xFFFFFF);
    access->mutable_thumbnail()->mutable_foreground()->set_rgb(0xADD8E6);
  }

  peer_ = peer;

  directoryList_.setDirectory(File::getSpecialLocation(START_DIR), true, true);
  directoryListThread_.startThread(THREAD_PRIORITY);

  peer_->fileTreeComp->setColour(BACKGROUND, FOREGROUND);
  peer_->fileTreeComp->addListener(this);

  Description d = rec::slow::getPreferences()->get().timescale();

  peer_->timeScaleSlider->setValue(d.time_scale());
  peer_->pitchScaleSlider->setValue(d.pitch_scale());

  peer_->timeScaleSlider->addListener(this);
  peer_->pitchScaleSlider->addListener(this);
  peer_->zoomSlider->addListener(this);

#ifdef USE_CDBURNERS
  burners_.resize(cdNames_.size());
  for (int i = 0; i < burners_.size(); ++i) {
    burners_[i] = AudioCDBurner::openDevice(i);
    burners_[i]->addChangeListener(this);
    changeListenerCallback(burners_[i]);
  }
#endif

  transportSource_.addChangeListener(this);
  deviceManager_->addAudioCallback(&player_);
  player_.setSource(&transportSource_);
  rec::audio::format::mpg123::initializeOnce();

  cursorThread_.reset(new CursorThread(this));
  cursorThread_->startThread();
}

void MainPageK::destruct() {
  // TODO: why does this have to be called so early in the destructor sequence?
  // Can we get rid of all of this entirely?
  cursorThread_->signalThreadShouldExit();
  transportSource_.setSource(NULL);
  player_.setSource(NULL);

  deviceManager_->removeAudioCallback(&player_);
  peer_->fileTreeComp->removeListener(this);

#if 0
  for (int i = 0; i < burners_.size(); ++i)
    delete burners_[i];

  burners_.clear();
#endif
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

    Description d = rec::slow::getPreferences()->get().timescale();
    AudioFormatReaderSource *s0 = new AudioFormatReaderSource(r0, true);
    AudioFormatReaderSource *s1 = new AudioFormatReaderSource(r1, true);

    stretchyDeleter_.reset(new DoubleStretchyThread(d, s0, s1));
    stretchyDeleter_.swap(stretchy_);

    loopingButtonClicked();
    transportSource_.setSource(stretchy_.get());

  } else {
    LOG(ERROR) << "Didn't understand file type for filename "
               << file.getFullPathName();
  }
}

void MainPageK::sliderValueChanged(Slider* slider) {
  if (slider == peer_->zoomSlider)
    peer_->thumbnail->setZoomFactor(slider->getValue());
}

void MainPageK::sliderDragEnded(Slider* slider) {
  {
    Data<rec::slow::Preferences>::Access access(rec::slow::getPreferences());
    if (slider == peer_->timeScaleSlider)
      access->mutable_timescale()->set_time_scale(slider->getValue());

    else if (slider == peer_->pitchScaleSlider)
      access->mutable_timescale()->set_pitch_scale(slider->getValue());

    else
      return;

    if (stretchy_)
      stretchy_->setDescription(access->timescale());
  }
}

static const char* const CD_STATE_NAMES[] = {
  "unknown",                /**< An error condition, if the device isn't responding. */
  "trayOpen",               /**< The drive is currently open. Note that a slot-loading drive
                               may seem to be permanently open. */
  "noDisc",                 /**< The drive has no disk in it. */
  "Writablediskpresent",    /**< The drive contains a writeable disk. */
  "readOnlyDiskPresent"     /**< The drive contains a read-only disk. */
};

#ifdef USE_CDBURNERS
void MainPageK::changeListenerCallback(void* objectThatHasChanged) {
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

#else

void MainPageK::changeListenerCallback(void* objectThatHasChanged) {
  CHECK_EQ(objectThatHasChanged, &transportSource_);
  double position = transportSource_.getCurrentPosition();
  peer_->thumbnail->setCursor(position);
}

#endif

void MainPageK::startStopButtonClicked() {
  if (transportSource_.isPlaying()) {
    transportSource_.stop();
  } else {
    transportSource_.setPosition(0);
    transportSource_.start();
  }
}

void MainPageK::loopingButtonClicked() {
  if (stretchy_)
    stretchy_->setLooping(peer_->loopingButton->getToggleState());
}

void MainPageK::selectionChanged() {
  peer_->zoomSlider->setValue(0, false, false);

  File file = peer_->fileTreeComp->getSelectedFile();
  peer_->thumbnail->setFile(file);
  loadFileIntoTransport(file);
}
