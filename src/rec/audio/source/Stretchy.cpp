#include <glog/logging.h>

#include "rec/audio/source/Stretchy.h"

namespace rec {
namespace audio {
namespace source {

Stretchy::Stretchy(const TimeStretch& description,
                   Source* source)
    : Wrappy::Position(source),
      description_(description),
      channels_(description.channels()),
      buffer_(channels_, SAMPLE_BUFFER_INITIAL_SIZE),
      outOffset_(channels_) {
  Init(description_, &scaler_);
}

int Stretchy::getTotalLength() {
  return source_->getTotalLength() / description_.time_scale();
}

void Stretchy::setNextReadPosition(int position) {
  ScopedLock l(lock_);

  position_ = position;
  source_->setNextReadPosition(position * description_.time_scale());
  Init(description_, &scaler_);
}

void Stretchy::getNextAudioBlock(const AudioSourceChannelInfo& info) {
  ScopedLock l(lock_);
  CHECK_EQ(info.buffer->getNumChannels(), channels_);

  bool foundZero = false;
  for (AudioSourceChannelInfo i = info; i.numSamples; ) {
    if (int processed = processOneChunk(i)) {
      i.numSamples -= processed;
      i.startSample += processed;
      position_ += processed;
      foundZero = false;
    } else if (foundZero) {
      LOG(ERROR)  << "0 samples twice in a row from Process(),"
                  << " asked for " << i.numSamples
                  << " from " << info.numSamples;
      return;
    } else {
      foundZero = true;
    }
  }
}

int Stretchy::processOneChunk(const AudioSourceChannelInfo& info) {
  ScopedLock l(lock_);

  int64 inSampleCount = scaler_.GetInputBufferSize(info.numSamples) / 2;
  getNextAudioBlockFromSource(inSampleCount);

  for (int c = 0; c < channels_; ++c)
    outOffset_[c] = info.buffer->getSampleData(c) + info.startSample;

  float** ins = buffer_.getArrayOfChannels();
  float** outs = &outOffset_.front();

  int samples = scaler_.Process(ins, outs, inSampleCount, info.numSamples);
  return samples;
}

void Stretchy::getNextAudioBlockFromSource(int numSamples) {
  ScopedLock l(lock_);
  buffer_.setSize(channels_, numSamples, false, false, true);

  AudioSourceChannelInfo i;
  i.startSample = 0;
  i.numSamples = numSamples;
  i.buffer = &buffer_;
  source_->getNextAudioBlock(i);
}

}  // namespace source
}  // namespace audio
}  // namespace rec
