#ifndef __REC_STRETCHY_AUDIO_SOURCE
#define __REC_STRETCHY_AUDIO_SOURCE

#include <vector>

#include "rec/audio/stretch/description.pb.h"

namespace rec {
namespace audio {
namespace source {

class Stretchy : public PositionableAudioSource {
 public:
  static const int SAMPLE_BUFFER_SIZE = 1000;

  Stretchable(const Description& description, PositionableAudioSource* source)
    : PositionableAudioSource("Stretchy"),
      description_(description),
      source_(source),
      position_(0),
      buffer_(description.channels(), SAMPLE_BUFFER_SIZE_),
      inOffset_(description.channels()),
      outOffset_(description.channels()) {
    Init(description_, &scaler_);
  }

  virtual int getNextReadPosition() {
    return position_;
  }

  virtual int getTotalLength() {
    return source_->getTotalLength() / description.timeScale();
  }

  virtual void setNextReadPosition(int position) {
    position_ = position;
    source_->setNextReadPosition(position * description.timeScale());
    Init(description_, &scaler_);
  }

  virtual void prepareToPlay(int samples, double rate) {
    source_->prepareToPlay(samples, rate);
  }

  virtual void releaseResources() {
    source_->releaseResources();
  }

  virtual void getNextAudioBlock(const AudioSourceChannelInfo& i) {
    AudioSourceChannelInfo info = i;
    while (info.numSamples) {
      int64 inSamples = scaler_.GetInputBufferSize(info->numSamples) / 2;
      buffer_.setSize(description_.channels(), inSamples, false, false, true);

      {
        AudioSourceChannelInfo sourceInfo;
        sourceInfo.startSample = 0;
        sourceInfo.numSamples = inSamples;
        sourceInfo.buffer = &buffer_;
        source_->getNextAudioBlock(sourceInfo);
      }

      for (int c = 0; c < desc_.channels; ++c)
        outOffset_[c] = info->buffer->getSampleData(c) + info->startSample;

      int processed = scaler_.Process(buffer_.getArrayOfChannels(),
                                      &outOffset.front(),
                                      inSamples,
                                      requested);
      info.numSamples -= processed;
      info.startSample += processed;
      position_ += processed;
    }
  }

 private:
  AudioSampleBuffer buffer_;
  AudioTimeScaler scaler_;
  std::vector<float*> outOffset_;
  int position_;

  DISALLOW_COPY_AND_ASSIGN(Stretchable);
};

}  // namespace source
}  // namespace audio
}  // namespace rec



#endif  // __REC_STRETCHY_AUDIO_SOURCE
