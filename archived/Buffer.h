#ifndef __REC_AUDIO_BUFFER
#define __REC_AUDIO_BUFFER

#include <vector>

#include "JuceLibraryCode/JuceHeader.h"
#include "rec/audio/stretch/TimeScaler.h"
#include "rec/base/scoped_ptr.h"
#include "rec/util/Circular.h"

namespace rec {
namespace audio {

struct Buffer : public rec::util::Circular {
  typedef std::vector<float*> Samples;

  Samples samples_;
  const AudioSampleBuffer* buffer_;

  Buffer() {}
  Buffer(const AudioSampleBuffer& audioBuffer, int sampleChannels)
      : Circular(audioBuffer.getNumSamples()),
        samples_(sampleChannels) {
    int channels = audioBuffer.getNumChannels();
    for (Samples::iterator i = samples_.begin(); i != samples_.end(); ++i)
      *i = audioBuffer.getSampleData((i - samples_.begin()) % channels);
  }

  void advance(int64 delta) {
    position_ += delta;
    for (Samples::iterator i = samples_.begin(); i != samples_.end(); ++i)
      *i += delta;
  }

  float** top() { return &samples_[0]; }
};

}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_BUFFER
