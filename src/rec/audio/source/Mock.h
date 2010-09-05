#ifndef __REC_MOCK_AUDIO_SOURCE
#define __REC_MOCK_AUDIO_SOURCE

#include "JuceLibraryCode/JuceHeader.h"
#include "rec/audio/Math.h"

namespace rec {
namespace audio {
namespace source {

class Mock : public AudioSource {
 public:
  Mock() : counter_(0) {}

  virtual void prepareToPlay (int samplesPerBlockExpected,
                              double sampleRate) {}

  virtual void releaseResources() {}

  virtual void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) {
    AudioSampleBuffer* buffer = bufferToFill.buffer;
    for (int i = 0; i < bufferToFill.numSamples; ++i, ++counter_)
      for (int j = 0; j < buffer->getNumChannels(); ++j)
        *buffer->getSampleData(j, bufferToFill.startSample + i) = getSample();
  }

 protected:
  int counter_;

  virtual float getSample() = 0;
};

}  // namespace source
}  // namespace audio
}  // namespace rec


#endif  // __REC_MOCK_AUDIO_SOURCE
