#ifndef __REC_STRETCHY_AUDIO_SOURCE
#define __REC_STRETCHY_AUDIO_SOURCE

// Wrap an incoming AudioSource, and time-stretch it.

#include <vector>

#include "rec/audio/source/Wrappy.h"
#include "rec/audio/stretch/Stretch.pb.h"

namespace rec {
namespace audio {
namespace stretch {

class Stretch;
class Implementation;

class Stretchy : public source::Wrappy {
 public:
  Stretchy(Source* s);
  void setStretch(const Stretch&);

  ~Stretchy();

  virtual int64 getTotalLength() const;
  virtual void setNextReadPosition(int64);
  virtual int64 getNextReadPosition() const;
  virtual void getNextAudioBlock(const juce::AudioSourceChannelInfo&);

 private:
  int64 processOneChunk(const juce::AudioSourceChannelInfo& info);
  int64 scale(int64 x) const { return static_cast<int64>(timeScale_ * x); }

  CriticalSection lock_;

  ptr<Implementation> implementation_;
  Stretch::Strategy strategy_;
  int channels_;
  double timeScale_;
  bool bypass_;

  DISALLOW_COPY_AND_ASSIGN(Stretchy);
};

}  // namespace stretch
}  // namespace audio
}  // namespace rec

#endif  // __REC_STRETCHY_AUDIO_SOURCE
