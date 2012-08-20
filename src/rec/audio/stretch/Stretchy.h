#ifndef __REC_STRETCHY_AUDIO_SOURCE
#define __REC_STRETCHY_AUDIO_SOURCE

// Wrap an incoming AudioSource, and time-stretch it.

#include <vector>

#include "rec/audio/source/Wrappy.h"
#include "rec/base/SampleRate.h"

namespace rec {
namespace audio {
namespace stretch {

class Stretch;
class StretchParameters;
class Implementation;

class Stretchy : public source::Wrappy {
 public:
  explicit Stretchy(Source*);
  Stretchy(Source*, const Stretchy&);

  void init(SampleRate);

  ~Stretchy();

  virtual int64 getTotalLength() const;
  virtual void setNextReadPosition(int64);
  virtual int64 getNextReadPosition() const;
  virtual void getNextAudioBlock(const juce::AudioSourceChannelInfo&);

  Implementation* implementation() { return implementation_.get(); }

 private:
  double timeScale() const;
  int64 processOneChunk(const juce::AudioSourceChannelInfo& info);
  ptr<Implementation> implementation_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(Stretchy);
};

}  // namespace stretch
}  // namespace audio
}  // namespace rec

#endif  // __REC_STRETCHY_AUDIO_SOURCE
