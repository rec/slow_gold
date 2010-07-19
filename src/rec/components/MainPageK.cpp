#include "MainPageJ.h"
#include "MainPageK.h"

#include "AudioThumbnailComponent.h"
#include "rec/audio/Math.h"
#include "JuceLibraryCode/JuceHeader.h"
#include "rec/audio/format/mpg123/Mpg123.h"

using rec::audio::timescaler::Description;
using rec::audio::source::Loop;
using rec::audio::format::mpg123::getFileReader;

// TODO: why can't this be defined in the .h with other primitives?!

const TreeView::ColourIds MainPageK::BACKGROUND = FileTreeComponent::backgroundColourId;
const Colour MainPageK::FOREGROUND = Colours::white;
const File::SpecialLocationType MainPageK::START_DIR = File::userHomeDirectory;
const char* MainPageK::PREVIEW_THREAD_NAME = "audio file preview";

MainPageK::MainPageK(AudioDeviceManager* d)
  : deviceManager_(d),
    directoryListThread_(PREVIEW_THREAD_NAME),
    directoryList_(NULL, directoryListThread_),
    scaleDescription_(Description::Default()),
    cdNames_(AudioCDBurner::findAvailableDevices()) {
}

void MainPageK::construct(MainPageJ* peer) {
  peer_ = peer;

  directoryList_.setDirectory(File::getSpecialLocation(START_DIR), true, true);
  directoryListThread_.startThread(THREAD_PRIORITY);

  peer_->fileTreeComp->setColour(BACKGROUND, FOREGROUND);
  peer_->fileTreeComp->addListener(this);

  deviceManager_->addAudioCallback(&player_);

  peer_->timeScaleSlider->setValue(scaleDescription_.timeScale_);
  peer_->pitchScaleSlider->setValue(scaleDescription_.pitchScale_);
  player_.setSource(&transportSource_);

  peer_->timeScaleSlider->addListener(this);
  peer_->pitchScaleSlider->addListener(this);
  peer_->zoomSlider->addListener(this);

  burners_.resize(cdNames_.size());
  for (int i = 0; i < burners_.size(); ++i) {
    burners_[i] = AudioCDBurner::openDevice(i);
    burners_[i]->addChangeListener(this);
    changeListenerCallback(burners_[i]);
  }
}

void MainPageK::destruct() {
  // TODO: why does this have to be called so early in the destructor sequence?
  // Can we get rid of all of this entirely?
  transportSource_.setSource(NULL);
  player_.setSource(NULL);

  deviceManager_->removeAudioCallback(&player_);
  peer_->fileTreeComp->removeListener(this);

  for (int i = 0; i < burners_.size(); ++i)
    delete burners_[i];

  burners_.clear();
}

void MainPageK::sliderValueChanged(Slider* slider) {
  if (slider == peer_->zoomSlider)
    peer_->thumbnail->setZoomFactor(slider->getValue());
}

void MainPageK::sliderDragEnded(Slider* slider) {
  if (slider == peer_->timeScaleSlider)
    scaleDescription_.timeScale_ = slider->getValue();

  else if (slider == peer_->pitchScaleSlider)
    scaleDescription_.pitchScale_ = slider->getValue();

  else
    return;

  scaleTime();
}

static const char* const CD_STATE_NAMES[] = {
  "unknown",                /**< An error condition, if the device isn't responding. */
  "trayOpen",               /**< The drive is currently open. Note that a slot-loading drive
                                     may seem to be permanently open. */
  "noDisc",                 /**< The drive has no disk in it. */
  "writableDiskPresent",    /**< The drive contains a writeable disk. */
  "readOnlyDiskPresent"     /**< The drive contains a read-only disk. */
};

void MainPageK::changeListenerCallback(void* objectThatHasChanged) {
  AudioCDBurner* cd = (AudioCDBurner*) objectThatHasChanged;
  std::cerr << CD_STATE_NAMES[cd->getDiskState()] << "\n";
}

void MainPageK::startStopButtonClicked() {
  if (transportSource_.isPlaying()) {
    transportSource_.stop();
  } else {
    transportSource_.setPosition(0);
    transportSource_.start();
  }
}

void MainPageK::loopingButtonClicked() {
  // how do deal with this?
}

void MainPageK::selectionChanged() {
  peer_->zoomSlider->setValue(0, false, false);

  File file = peer_->fileTreeComp->getSelectedFile();
  peer_->thumbnail->setFile(file);
  loadFileIntoTransport(file);
}

void MainPageK::loadFileIntoTransport(const File& file) {
  scoped_ptr<AudioFormatReader> reader(getFileReader(file));
  if (reader) {
    transportSource_.stop();
    transportSource_.setSource(NULL);

    int length = reader->lengthInSamples;
    loopBuffer_.reset(new AudioSampleBuffer(reader->numChannels, length));
    loopBuffer_->readFromAudioReader(reader.get(), 0, length, 0, true, true);

    scaleTime();
  } else {
    std::cerr << "Didn't understand file type for filename "
    << file.getFileName()
    << std::endl;
  }
}

bool MainPageK::scaleTime() {
  transportSource_.stop();
  if (!stretch_.requestRescale(scaleDescription_, *loopBuffer_, &scaledBuffer_))
    return false;

  loop_.reset(new Loop(*scaledBuffer_));
  loop_->setNextReadPosition(0);

  transportSource_.setSource(loop_.get());
  return true;
}
