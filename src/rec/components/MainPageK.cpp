#include "MainPageJ.h"
#include "MainPageK.h"

#include "DemoThumbnailComp.h"
#include "rec/audio/source/Stretchable.h"
#include "rec/audio/Math.h"
#include "JuceLibraryCode/JuceHeader.h"

using rec::audio::source::BufferDescription;
using rec::audio::source::Loop;

const TreeView::ColourIds MainPageK::BACKGROUND = FileTreeComponent::backgroundColourId;
const Colour MainPageK::FOREGROUND = Colours::white;
const File::SpecialLocationType MainPageK::START_DIR = File::userHomeDirectory;
const char* MainPageK::PREVIEW_THREAD_NAME = "audio file preview";

MainPageK::MainPageK(AudioDeviceManager* d)
  : deviceManager_(d),
    directoryListThread_(PREVIEW_THREAD_NAME),
    directoryList_(NULL, directoryListThread_) {
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
    int length = reader->lengthInSamples;
    loopBuffer_.reset(new AudioSampleBuffer(reader->numChannels,
                                            length + LOOP_BUFFER_WRAPAROUND));
    loopBuffer_->readFromAudioReader(reader.get(), 0, length, 0, true, true);

    rec::audio::math::wraparound(length, LOOP_BUFFER_WRAPAROUND, loopBuffer_.get());
    loop_.reset(new Loop(*loopBuffer_));

    loop_->setNextReadPosition(0);

    // transportSource_.setSource(*stretchable_.get());

  } else {
    std::cerr << "Didn't understand file type for filename "
              << file.getFileName()
              << std::endl;
  }
}

void MainPageK::selectionChanged() {
  peer_->zoomSlider->setValue(0, false, false);

  File file = peer_->fileTreeComp->getSelectedFile();
  peer_->thumbnail->setFile(file);
  loadFileIntoTransport(file);
}

