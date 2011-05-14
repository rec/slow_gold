#include "rec/audio/source/Stretchy.h"

using namespace juce;
using namespace google;

using rec::audio::stretch::Stretch;

namespace rec {
namespace audio {
namespace source {

Stretchy::Stretchy(PositionableAudioSource* s) : Wrappy(s), initialized_(false) {
}

Stretchy::~Stretchy() {}

int64 Stretchy::getTotalLength() const {
  ScopedLock l(lock_);
  return source()->getTotalLength() * timeScale_;
}

int64 Stretchy::getNextReadPosition() const {
  ScopedLock l(lock_);
  return source()->getNextReadPosition() * timeScale_;
}

void Stretchy::setNextReadPosition(int64 position) {
  ScopedLock l(lock_);
  source()->setNextReadPosition(position / timeScale_);
}

void Stretchy::setStretch(const stretch::Stretch& s) {
  ScopedLock l(lock_);
  stretch_ = s;
  initialized_ = false;
}

void Stretchy::initialize() {
  ScopedLock l(lock_);
  if (initialized_)
    return;

  channels_ = stretch_.channels();
  if (!buffer_ || buffer_->getNumChannels() != channels_)
    buffer_.reset(new Buffer(channels_, SAMPLE_BUFFER_INITIAL_SIZE));
  outOffset_.resize(channels_);
  timeScale_ = timeScale(stretch_);
  audio::stretch::Init(stretch_, &scaler_);
  initialized_ = true;
}

void Stretchy::getNextAudioBlock(const AudioSourceChannelInfo& info) {
  ScopedLock l(lock_);
  initialize();

  DCHECK_EQ(info.buffer->getNumChannels(), channels_);
  int zeroCount = 0;
  for (AudioSourceChannelInfo i = info; i.numSamples; ) {
    if (int processed = processOneChunk(i)) {
      if (zeroCount) {
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
        << "next read source " << source()->getNextReadPosition();
      return;

    } else {
      ++zeroCount;
    }
  }
}

int64 Stretchy::processOneChunk(const AudioSourceChannelInfo& info) {
  int64 inSampleCount = scaler_.GetInputBufferSize(info.numSamples) / 2;
  buffer_->setSize(stretch_.channels(), inSampleCount, false, false, true);

  AudioSourceChannelInfo i;
  i.startSample = 0;
  i.numSamples = inSampleCount;
  i.buffer = buffer_.get();
  source()->getNextAudioBlock(i);

  for (int c = 0; c < channels_; ++c)
    outOffset_[c] = info.buffer->getSampleData(c) + info.startSample;

  float** ins = buffer_->getArrayOfChannels();
  float** outs = &outOffset_.front();

  int64 samples = scaler_.Process(ins, outs, inSampleCount, info.numSamples);
  return samples;
}

}  // namespace source
}  // namespace audio
}  // namespace rec
