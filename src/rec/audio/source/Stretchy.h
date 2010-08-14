#ifndef __REC_STRETCHY_AUDIO_SOURCE
#define __REC_STRETCHY_AUDIO_SOURCE

#include <vector>
#include <glog/logging.h>

#include "rec/audio/stretch/description.pb.h"
#include "rec/audio/source/Wrappy.h"

namespace rec {
namespace audio {
namespace source {

template <typename Source>
class Stretchy : public PositionWrappy<Source> {
 public:
  static const int SAMPLE_BUFFER_INITIAL_SIZE = 1000;

  Stretchy(const Description& description, Source* source)
    : PositionWrappy<Source>("Stretchy", source),
      description_(description),
      channels_(description.channels()),
      buffer_(channels_, SAMPLE_BUFFER_INITIAL_SIZE),
      inOffset_(channels_),
      outOffset_(channels_) {
    Init(description_, &scaler_);
  }

  virtual int getTotalLength() {
    return source_->getTotalLength() / description.timeScale();
  }

  virtual void setNextReadPosition(int position) {
    position_ = position;
    source_->setNextReadPosition(position * description.timeScale());
    Init(description_, &scaler_);
  }

  virtual void getNextAudioBlock(const AudioSourceChannelInfo& info) {
    CHECK_EQ(info.buffer->getNumChannels(), channels_);

    for (AudioSourceChannelInfo i = info; i.numSamples; ) {
      if (int processed = processOneChunk(i)) {
        i.numSamples -= processed;
        i.startSample += processed;
        position_ += processed;
      } else {
        LOG_FIRST_N(DFATAL, 20) << "0 samples in Stretchy::getNextAudioBlock()";
        return;
      }
    }
  }

 private:
  int processOneChunk(const AudioSourceChannelInfo& info) {
    int64 inSampleCount = scaler_.GetInputBufferSize(info->numSamples) / 2;
    getNextAudioBlockFromSource(inSampleCount);

    for (int c = 0; c < channels_; ++c)
      outOffset_[c] = info->buffer->getSampleData(c) + info->startSample;

    float** inSamples = buffer_.getArrayOfChannels();
    float** outSamples = &outOffset_.front();

    return scaler_.Process(inSamples, outSamples,
                           inSampleCount, info->numSamples);
  }

  void getNextAudioBlockFromSource(int numSamples) {
    buffer_.setSize(channels_, numSamples, false, false, true);

    AudioSourceChannelInfo i;
    i.startSample = 0;
    i.numSamples = numSamples;
    i.buffer = &buffer_;
    source_->getNextAudioBlock(i);
  }

  const Description description_;
  Source* const source_;
  const int channels_;
  bool isLooping_;
  AudioSampleBuffer buffer_;
  AudioTimeScaler scaler_;
  std::vector<float*> outOffset_;

  DISALLOW_COPY_AND_ASSIGN(Stretchy);
};

}  // namespace source
}  // namespace audio
}  // namespace rec



#endif  // __REC_STRETCHY_AUDIO_SOURCE
