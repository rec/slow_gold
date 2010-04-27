#include "MainPageJ.h"
#include "MainPageK.h"

#include "DemoThumbnailComp.h"
#include "rec/audio/source/Stretchable.h"
#include "JuceLibraryCode/JuceHeader.h"

using rec::audio::source::BufferDescription;

void MainPageK::construct(MainPageJ* peer) {
  peer_ = peer;

  File file = File::getSpecialLocation(File::userHomeDirectory);
  directoryList_.setDirectory(file, true, true);
  thread_.startThread(3);

  peer_->fileTreeComp->setColour(FileTreeComponent::backgroundColourId,
                                 Colours::white);
  peer_->fileTreeComp->addListener(this);

  deviceManager_->addAudioCallback(&player_);
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
  source_->setLooping(peer_->loopingButton->getToggleState());
}

void MainPageK::zoomSliderChanged(double value) {
  peer_->thumbnail->setZoomFactor(value);
}

void MainPageK::loadFileIntoTransport(const File& audioFile) {
  // unload the previous file source and delete it..
  transportSource_.stop();
  if (stretchable_)
    stretchable_->shutdown();

  transportSource_.setSource(NULL);
  stretchable_.reset();
  source_.reset();

  AudioFormatManager formatManager;
  formatManager.registerBasicFormats();

  if (AudioFormatReader* reader = formatManager.createReaderFor(audioFile)) {
    source_.reset(new AudioFormatReaderSource(reader, true));
    source_->setLooping(true);
    transportSource_.setSource(source_.get(), READAHEAD_SIZE, reader->sampleRate);

    stretchable_.reset(new Stretchable(BufferDescription::DEFAULT));
    stretchable_->setSource(&transportSource_);
    player_.setSource(stretchable_.get());
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

