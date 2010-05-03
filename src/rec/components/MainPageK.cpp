#include "MainPageJ.h"
#include "MainPageK.h"

#include "DemoThumbnailComp.h"
#include "rec/audio/source/Stretchable.h"
#include "JuceLibraryCode/JuceHeader.h"

using rec::audio::source::BufferDescription;

const TreeView::ColourIds MainPageK::BACKGROUND = FileTreeComponent::backgroundColourId;
const Colour MainPageK::FOREGROUND = Colours::white;
const File::SpecialLocationType MainPageK::START_DIR = File::userHomeDirectory;
const char* MainPageK::PREVIEW_THREAD_NAME = "audio file preview";

MainPageK::MainPageK(AudioDeviceManager* d)
  : deviceManager_(d),
    directoryListThread_(PREVIEW_THREAD_NAME),
    directoryList_(NULL, directoryListThread_),
    loopBuffer_(LOOP_BUFFER_CHANNELS, LOOP_BUFFER_SIZE),
    loop_(loopBuffer_) {
}

void MainPageK::construct(MainPageJ* peer) {
  peer_ = peer;

  directoryList_.setDirectory(File::getSpecialLocation(START_DIR), true, true);
  directoryListThread_.startThread(THREAD_PRIORITY);

  peer_->fileTreeComp->setColour(BACKGROUND, FOREGROUND);
  peer_->fileTreeComp->addListener(this);

  deviceManager_->addAudioCallback(&player_);
  player_.setSource(&transportSource_);
}

void MainPageK::destruct() {
  // TODO: why does this have to be called so early in the destructor sequence?
  // Can we get rid of all of this entirely?
  transportSource_.setSource(NULL);
  player_.setSource(NULL);

  deviceManager_->removeAudioCallback(&player_);
  peer_->fileTreeComp->removeListener(this);
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

void MainPageK::zoomSliderChanged(double value) {
  peer_->thumbnail->setZoomFactor(value);
}

void MainPageK::loadFileIntoTransport(const File& file) {
  transportSource_.stop();
  if (stretchable_)
    stretchable_->shutdown();

  transportSource_.setSource(NULL);
  stretchable_.reset();

  AudioFormatManager formatManager;
  formatManager.registerBasicFormats();

  scoped_ptr<AudioFormatReader> reader(formatManager.createReaderFor(file));
  if (reader) {
    int length = readFromAudioReader->lengthInSamples;
    loopBuffer_.setSize(reader->numChannels, length + LOOP_BUFFER_WRAPAROUND);
    loopBuffer_.readFromAudioReader(r, 0, length, 0, true, true);

    // Now make the buffer wrap around a little for ease in shifting...
    int wraparoundSize = LOOP_BUFFER_WRAPAROUND * sizeof(float);
    for (int c = 0; c < loopBuffer_->numChannels; ++c) {
      float* start = loopBuffer_.getSampleData(c);
      memcpy(start + length, start, wraparoundSize);
    }

    loop_.setNextReadPosition(0);

    stretchable_.reset(new rec::audio::source::Stretchable(BufferDescription::DEFAULT));
    stretchable_->setSource(&loop_);
    transportSource_.setSource(*stretchable_.get());
  } else {
    std::cerr << "Didn't understand file type for filename "
              << audioFile.getFileName()
              << std::endl;
  }
}

void MainPageK::selectionChanged() {
  peer_->zoomSlider->setValue(0, false, false);

  File file = peer_->fileTreeComp->getSelectedFile();
  peer_->thumbnail->setFile(file);
  loadFileIntoTransport(file);
}

