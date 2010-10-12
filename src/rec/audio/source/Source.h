#ifndef __REC_AUDIO_SOURCE_SOURCE__
#define __REC_AUDIO_SOURCE_SOURCE__

#include "rec/base/base.h"

#include "JuceLibraryCode/JuceHeader.h"

namespace rec {
namespace audio {
namespace source {

typedef juce::PositionableAudioSource Source;

class SourceMaker {
  virtual Source* make() const;
  ~SourceMaker() {}
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_SOURCE__
