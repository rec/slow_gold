#ifndef __REC_STRETCHABLE_AUDIO_SOURCE
#define __REC_STRETCHABLE_AUDIO_SOURCE

#include <vector>

#include "rec/audio/source/BufferedWrapper.h"

namespace rec {
namespace audio {
namespace source {

class Stretchable : public BufferedWrapper {
 public:
  const static int STRETCH_BUFFER_RATIO = 200;

  Stretchable(const BufferDescription& d)
      : BufferedWrapper("Stretchable", d),
        buffer_(d.channels, d.samples * STRETCH_BUFFER_RATIO) {
  }

  virtual void init() {
    Init(rec::audio::timescaler::Description(), &scaler_);
    BufferedWrapper::init();
  }

  virtual void fillOneBuffer(AudioSampleBuffer *toFill) {
    int64 samplesProcessed = 0;
    std::vector<float*> outOffset(desc_.channels);

    for (int i = 0; samplesProcessed < desc_.samples && i < 5; ++i) {
      int64 requested = desc_.samples - samplesProcessed;
      int64 inSamples = scaler_.GetInputBufferSize(requested) / 2;

      if (inSamples > buffer_.getNumSamples())
        buffer_.setSize(buffer_.getNumChannels(), inSamples);

      AudioSourceChannelInfo info;
      info.startSample = 0;
      info.numSamples = inSamples;
      info.buffer = &buffer_;
      source_->getNextAudioBlock(info);

      for (int c = 0; c < desc_.channels; ++c)
        outOffset[c] = toFill->getSampleData(c) + samplesProcessed;

      samplesProcessed += scaler_.Process(buffer_.getArrayOfChannels(),
                                          &outOffset.front(), inSamples,
                                          requested);
    }
    jassert(samplesProcessed == desc_.samples);
  }

 private:
  AudioSampleBuffer buffer_;
  AudioTimeScaler scaler_;

  DISALLOW_COPY_AND_ASSIGN(Stretchable);
};

}  // namespace source
}  // namespace audio
}  // namespace rec



#endif  // __REC_STRETCHABLE_AUDIO_SOURCE
