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

  deviceManager_->addAudioCallback(&audioSourcePlayer_);
}

void MainPageK::destruct() {
  // TODO: why does this have to be called so early in the destructor sequence?
  // Can we get rid of all of this entirely?
  transportSource_.setSource(NULL);
  audioSourcePlayer_.setSource(NULL);

  deviceManager_->removeAudioCallback(&audioSourcePlayer_);
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
  audioSource_->setLooping(peer_->loopingButton->getToggleState());
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
  audioSource_.reset();

  // get a format manager and set it up with the basic types (wav and aiff).
  AudioFormatManager formatManager;
  formatManager.registerBasicFormats();

  if (AudioFormatReader* reader = formatManager.createReaderFor(audioFile)) {
    audioSource_.reset(new AudioFormatReaderSource(reader, true));
    audioSource_->setLooping(true);

    // ..and plug it into our transport source
    transportSource_.setSource(audioSource_.get(),
                              32768, // tells it to buffer this many samples ahead
                              reader->sampleRate);

    stretchable_.reset(new Stretchable(BufferDescription::DEFAULT));

    stretchable_->setSource(&transportSource_);
    audioSourcePlayer_.setSource(stretchable_.get());
  }
}

void MainPageK::selectionChanged() {
  peer_->zoomSlider->setValue(0, false, false);

  File file = peer_->fileTreeComp->getSelectedFile();
  peer_->thumbnail->setFile(file);
  loadFileIntoTransport(file);
}

