#ifndef __REC_STRETCHY_AUDIO_SOURCE
#define __REC_STRETCHY_AUDIO_SOURCE

// Wrap an incoming AudioSource, and time-stretch it.

#include <vector>

#include "rec/audio/source/Wrappy.h"
#include "rec/audio/stretch/Stretch.h"
#include "rec/audio/stretch/Stretch.pb.h"
#include "rec/audio/stretch/TimeScaler.h"

class AudioTimeScaler;

namespace rec {
namespace audio {
namespace source {

class Stretchy : public Wrappy {
 public:
  typedef stretch::Stretch Stretch;

  void setStretch(const Stretch&);

  ~Stretchy();

  virtual int64 getTotalLength() const;
  virtual void setNextReadPosition(int64);
  virtual int64 getNextReadPosition() const;
  virtual void getNextAudioBlock(const juce::AudioSourceChannelInfo&);

  static
  Stretchy* create(Source*, const Stretch& s = Stretch::default_instance());

 protected:
  Stretchy(Source* s, const Stretch& stretch = Stretch::default_instance());

  virtual void initializeStretcher() = 0;
  virtual void nextStretchedAudioBlock(const AudioSourceChannelInfo&) = 0;

  Stretch stretch_;
  std::vector<float*> outOffset_;

 private:
  int64 processOneChunk(const juce::AudioSourceChannelInfo& info);
  int64 scale(int64 x) const { return static_cast<int64>(timeScale_ * x); }

  CriticalSection lock_;

  double timeScale_;
  bool bypass_;

  DISALLOW_COPY_AND_ASSIGN(Stretchy);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_STRETCHY_AUDIO_SOURCE
