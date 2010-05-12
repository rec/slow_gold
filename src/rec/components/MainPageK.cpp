#include "MainPageJ.h"
#include "MainPageK.h"

#include "DemoThumbnailComp.h"
#include "rec/audio/source/Stretchable.h"
#include "rec/audio/Math.h"
#include "JuceLibraryCode/JuceHeader.h"

using rec::audio::source::BufferDescription;
using rec::audio::timescaler::Description;
using rec::audio::source::Loop;

// TODO: why can't this be defined in the .h with other primitives?!
const int MainPageK::CHUNK_SIZE = 512;

const TreeView::ColourIds MainPageK::BACKGROUND = FileTreeComponent::backgroundColourId;

const Colour MainPageK::FOREGROUND = Colours::white;

const File::SpecialLocationType MainPageK::START_DIR = File::userHomeDirectory;

const char* MainPageK::PREVIEW_THREAD_NAME = "audio file preview";

MainPageK::MainPageK(AudioDeviceManager* d)
  : deviceManager_(d),
    directoryListThread_(PREVIEW_THREAD_NAME),
    directoryList_(NULL, directoryListThread_),
    scaleDescription_(Description::Default()){
}

void MainPageK::sliderValueChanged(Slider* slider) {
  if (slider == peer_->zoomSlider)
    peer_->thumbnail->setZoomFactor(slider->getValue());
}

void MainPageK::sliderDragEnded(Slider* slider) {
  if (slider == peer_->timeScaleSlider) {
    scaleDescription_.timeScale_ = slider->getValue();
    scaleTime();
  } else if (slider == peer_->pitchScaleSlider) {
    scaleDescription_.pitchScale_ = slider->getValue();
    scaleTime();
  }
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

void MainPageK::scaleTime() {
  if (!loopBuffer_)
    return;

  double timeScale = scaleDescription_.timeScale_;
  int outChannels = scaleDescription_.channels_;
  int inChannels = loopBuffer_->getNumChannels();
  int samples = loopBuffer_->getNumSamples();
  int scaledSamples = loopBuffer_->getNumSamples() * timeScale;

  scaledBuffer_.reset(new AudioSampleBuffer(outChannels, scaledSamples));

  AudioTimeScaler scaler;
  scaleDescription_.Init(&scaler);

  std::vector<float*> inSamples(inChannels), outSamples(outChannels);

  for (int written = 0, read = 0; written < scaledSamples && read < samples; ) {
    int outChunk = std::min(CHUNK_SIZE, scaledSamples - written);
    int64 inChunk = std::min(scaler.GetInputBufferSize(outChunk) / 2,
                             (unsigned) (samples - read));

    for (int c = 0; c < std::max(inChannels, outChannels); ++c) {
      inSamples[c] = loopBuffer_->getSampleData(c % inChannels) + read;
      outSamples[c] = scaledBuffer_->getSampleData(c % outChannels) + written;
    }

    written += scaler.Process(&inSamples[0], &outSamples[0], inChunk, outChunk);
    read += inChunk;
  }

  loop_.reset(new Loop(*scaledBuffer_.get()));
  loop_->setNextReadPosition(0);

  transportSource_.setSource(loop_.get());
}

void MainPageK::loadFileIntoTransport(const File& file) {
  transportSource_.stop();

  transportSource_.setSource(NULL);

  AudioFormatManager formatManager;
  formatManager.registerBasicFormats();

  scoped_ptr<AudioFormatReader> reader(formatManager.createReaderFor(file));
  if (reader) {
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

void MainPageK::selectionChanged() {
  peer_->zoomSlider->setValue(0, false, false);

  File file = peer_->fileTreeComp->getSelectedFile();
  peer_->thumbnail->setFile(file);
  loadFileIntoTransport(file);
}

