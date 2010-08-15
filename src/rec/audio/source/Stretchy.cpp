#include <glog/logging.h>

#include "rec/audio/source/Stretchy.h"

namespace rec {
namespace audio {
namespace source {

template <typename Source>
Stretchy<Source>::Stretchy(const Description& description, Source* source)
    : PositionWrappy<Source>(source),
      description_(description),
      channels_(description.channels()),
      buffer_(channels_, SAMPLE_BUFFER_INITIAL_SIZE),
      outOffset_(channels_) {
  Init(description_, &scaler_);
}

template <typename Source>
int Stretchy<Source>::getTotalLength() {
  return this->source_->getTotalLength() / description_.time_scale();
}

template <typename Source>
void Stretchy<Source>::setNextReadPosition(int position) {
  this->position_ = position;
  this->source_->setNextReadPosition(position * description_.time_scale());
  Init(description_, &scaler_);
}

template <typename Source>
void Stretchy<Source>::getNextAudioBlock(const AudioSourceChannelInfo& info) {
  CHECK_EQ(info.buffer->getNumChannels(), channels_);

  for (AudioSourceChannelInfo i = info; i.numSamples; ) {
    if (int processed = processOneChunk(i)) {
      i.numSamples -= processed;
      i.startSample += processed;
      this->position_ += processed;
    } else {
      LOG_FIRST_N(ERROR, 20) << "0 samples in getNextAudioBlock()";
      return;
    }
  }
}

template <typename Source>
int Stretchy<Source>::processOneChunk(const AudioSourceChannelInfo& info) {
  int64 inSampleCount = scaler_.GetInputBufferSize(info.numSamples) / 2;
  getNextAudioBlockFromSource(inSampleCount);

  for (int c = 0; c < channels_; ++c)
    outOffset_[c] = info.buffer->getSampleData(c) + info.startSample;

  float** inSamples = buffer_.getArrayOfChannels();
  float** outSamples = &outOffset_.front();

  return scaler_.Process(inSamples, outSamples,
                         inSampleCount, info.numSamples);
}

template <typename Source>
void Stretchy<Source>::getNextAudioBlockFromSource(int numSamples) {
  buffer_.setSize(channels_, numSamples, false, false, true);

  AudioSourceChannelInfo i;
  i.startSample = 0;
  i.numSamples = numSamples;
  i.buffer = &buffer_;
  this->source_->getNextAudioBlock(i);
}

}  // namespace source
}  // namespace audio
}  // namespace rec
