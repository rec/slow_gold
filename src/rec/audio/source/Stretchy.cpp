#include <glog/logging.h>

#include "rec/audio/source/Stretchy.h"

#include "rec/audio/ammf_scaler/AudioTimeScaler.h"
#include "rec/audio/source/TimeScaler.h"
#include "rec/audio/source/TimeStretch.pb.h"

using namespace juce;

namespace rec {
namespace audio {
namespace source {

Stretchy::Stretchy(Source* s)
    : Wrappy::Position(s),
      description_(new TimeStretch),
      scaler_(new AudioTimeScaler),
      buffer_(2, SAMPLE_BUFFER_INITIAL_SIZE) {
}

Stretchy::~Stretchy() {}

void Stretchy::setDescription(const TimeStretch& d) {
  description_->CopyFrom(d);
  channels_ = d.channels();
  buffer_.setSize(channels_, SAMPLE_BUFFER_INITIAL_SIZE, false, false, true);
  outOffset_.resize(channels_);

  setNextReadPosition(position_);
}

int Stretchy::getTotalLength() const {
  return source_->getTotalLength() * description_->time_scale();
}

void Stretchy::setNextReadPosition(int position) {
  position_ = position;
  source_->setNextReadPosition(position / description_->time_scale());

#ifndef CATCH_EXCEPTIONS
  try {
#endif

    Init(*description_, scaler_.get());

#ifndef CATCH_EXCEPTIONS
  } catch (...) {
    LOG(ERROR) << "Couldn't Init";
  }
#endif
}

void Stretchy::getNextAudioBlock(const AudioSourceChannelInfo& info) {
  CHECK_EQ(info.buffer->getNumChannels(), channels_);
  int zeroCount = 0;
  for (AudioSourceChannelInfo i = info; i.numSamples; ) {
#ifndef CATCH_EXCEPTIONS
    try {
#endif
      if (int processed = processOneChunk(i)) {
        if (false && zeroCount) {
          LOG_FIRST_N(ERROR, 20) << "Got it on try " << (zeroCount + 1);
        }
        i.numSamples -= processed;
        i.startSample += processed;
        position_ += processed;
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
#ifndef CATCH_EXCEPTIONS
    } catch (...) {
      LOG(ERROR) << "Couldn't getNextAudioBlock";
      return;
    }
#endif
  }
}

int Stretchy::processOneChunk(const AudioSourceChannelInfo& info) {
  int64 inSampleCount = scaler_->GetInputBufferSize(info.numSamples) / 2;
  buffer_.setSize(channels_, inSampleCount, false, false, true);

  AudioSourceChannelInfo i;
  i.startSample = 0;
  i.numSamples = inSampleCount;
  i.buffer = &buffer_;
  source_->getNextAudioBlock(i);

  for (int c = 0; c < channels_; ++c)
    outOffset_[c] = info.buffer->getSampleData(c) + info.startSample;

  float** ins = buffer_.getArrayOfChannels();
  float** outs = &outOffset_.front();

  int samples = scaler_->Process(ins, outs, inSampleCount, info.numSamples);
  return samples;
}

}  // namespace source
}  // namespace audio
}  // namespace rec
