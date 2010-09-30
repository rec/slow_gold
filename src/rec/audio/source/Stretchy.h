#ifndef __REC_STRETCHY_AUDIO_SOURCE
#define __REC_STRETCHY_AUDIO_SOURCE

// Wrap an incoming AudioSource, and time-stretch it.

#include <vector>

#include "rec/audio/source/Wrappy.h"

class AudioTimeScaler;

namespace rec {
namespace audio {
namespace source {

class TimeStretch;

class Stretchy : public Wrappy::Position {
 public:
  static const int SAMPLE_BUFFER_INITIAL_SIZE = 1000;
  Stretchy(Source* s);
  ~Stretchy();

  void setDescription(const TimeStretch& d);

  virtual int getTotalLength() const;
  virtual void setNextReadPosition(int position);
  virtual void getNextAudioBlock(const AudioSourceChannelInfo& info);

  const TimeStretch& getDescription() const { return *description_; }

 private:
  int processOneChunk(const AudioSourceChannelInfo& info);

  scoped_ptr<TimeStretch> description_;
  int channels_;
  AudioSampleBuffer buffer_;
  scoped_ptr<AudioTimeScaler> scaler_;
  std::vector<float*> outOffset_;

  DISALLOW_COPY_AND_ASSIGN(Stretchy);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_STRETCHY_AUDIO_SOURCE
