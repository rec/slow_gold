#include <glog/logging.h>

#include "rec/audio/source/Stretchy.h"

using namespace juce;

namespace rec {
namespace audio {
namespace source {

Stretchy::Stretchy(const TimeStretch& desc, Source* s)
    : Wrappy(s),
      buffer_(desc.channels(), SAMPLE_BUFFER_INITIAL_SIZE),
      outOffset(desc.channels()) {
  DLOG(INFO) << "Creating stretchy with: " << this;
}

Stretchy::~Stretchy() {
  DLOG(INFO) << "Destroying stretchy with: " << this;
}

int Stretchy::getTotalLength() const {
  return source_->getTotalLength() * description_->time_scale();
}

int Stretchy::getNextReadPosition() {
  return source_->getNextReadPosition() * description_->time_scale();
}

void Stretchy::setNextReadPosition(int position) {
  source_->setNextReadPosition(position / description_->time_scale());
  Init(*description_, scaler_.get());
}

void Stretchy::getNextAudioBlock(const AudioSourceChannelInfo& info) {
  CHECK_EQ(info.buffer->getNumChannels(), description_.channels());
  int zeroCount = 0;
  for (AudioSourceChannelInfo i = info; i.numSamples; ) {
    if (int processed = processOneChunk(i)) {
      if (false && zeroCount) {
        LOG_FIRST_N(ERROR, 20) << "Got it on try " << (zeroCount + 1);
      }
      i.numSamples -= processed;
      i.startSample += processed;
      zeroCount = 0;

    } else if (zeroCount > 10) {
      LOG_FIRST_N(ERROR, 20)
        << "0 samples " << zeroCount << " times in a row,"
        << " asked for " << i.numSamples
        << " from " << info.numSamples
        << "next read " << getNextReadPosition()
        << "next read source " << source_->getNextReadPosition();
      return;

    } else {
      ++zeroCount;
    }
  }
}

int Stretchy::processOneChunk(const AudioSourceChannelInfo& info) {
  int64 inSampleCount = scaler_->GetInputBufferSize(info.numSamples) / 2;
  buffer_.setSize(description_.channels(), inSampleCount, false, false, true);

  AudioSourceChannelInfo i;
  i.startSample = 0;
  i.numSamples = inSampleCount;
  i.buffer = &buffer_;
  source_->getNextAudioBlock(i);

  for (int c = 0; c < description_.channels(); ++c)
    outOffset_[c] = info.buffer->getSampleData(c) + info.startSample;

  float** ins = buffer_.getArrayOfChannels();
  float** outs = &outOffset_.front();

  int samples = scaler_->Process(ins, outs, inSampleCount, info.numSamples);
  return samples;
}

}  // namespace source
}  // namespace audio
}  // namespace rec
