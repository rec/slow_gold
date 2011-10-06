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
  static const int SAMPLE_BUFFER_INITIAL_SIZE = 1000;

  ~Stretchy();

  void setStretch(const stretch::Stretch&);

  virtual int64 getTotalLength() const;
  virtual void setNextReadPosition(int64 position);
  virtual int64 getNextReadPosition() const;
  virtual void getNextAudioBlock(const juce::AudioSourceChannelInfo& info);
  void initialize();

  static Stretchy* create(PositionableAudioSource*);

 protected:
  Stretchy(PositionableAudioSource* s);

 private:
  int64 processOneChunk(const juce::AudioSourceChannelInfo& info);
  int64 scale(int64 x) const { return static_cast<int64>(timeScale_ * x); }

  stretch::Stretch stretch_;
  int channels_;
  ptr<AudioSampleBuffer> buffer_;
  ptr<AudioTimeScaler> scaler_;
  std::vector<float*> outOffset_;
  CriticalSection lock_;
  double timeScale_;
  bool initialized_;
  bool bypass_;

  DISALLOW_COPY_AND_ASSIGN(Stretchy);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_STRETCHY_AUDIO_SOURCE
