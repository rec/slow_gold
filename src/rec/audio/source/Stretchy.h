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

  typedef stretch::Stretch Stretch;

  void setStretch(const Stretch&);

  virtual int64 getTotalLength() const;
  virtual void setNextReadPosition(int64 position);
  virtual int64 getNextReadPosition() const;
  virtual void getNextAudioBlock(const juce::AudioSourceChannelInfo& info);
  void initialize();

  static Stretchy* create(PositionableAudioSource*,
                          const Stretch& stretch = Stretch::default_instance());

 protected:
  Stretchy(PositionableAudioSource* s,
           const Stretch& stretch = Stretch::default_instance());

  virtual void initializeStretcher() = 0;
  virtual int getInputSampleCount(int numSamples) const = 0;
  virtual int64 process(float** ins, int inSamples,
                        float** outs, int outSamples) = 0;

  Stretch stretch_;

 private:
  int64 processOneChunk(const juce::AudioSourceChannelInfo& info);
  int64 scale(int64 x) const { return static_cast<int64>(timeScale_ * x); }

  CriticalSection lock_;

  int channels_;
  ptr<AudioSampleBuffer> buffer_;
  std::vector<float*> outOffset_;
  double timeScale_;
  bool bypass_;

  DISALLOW_COPY_AND_ASSIGN(Stretchy);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_STRETCHY_AUDIO_SOURCE
