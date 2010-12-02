#ifndef __REC_AUDIO_SOURCE_DOUBLESTRETCHY__
#define __REC_AUDIO_SOURCE_DOUBLESTRETCHY__

// Wrap an incoming AudioSource, and time-stretch it.

#include "rec/audio/source/Source.h"

namespace rec {
namespace audio {
namespace source {

class BufferedStretchy;
class TimeStretch;

class DoubleStretchy : public Source {
 public:
  const static int MINIMUM_FILL_SIZE = 4096;

  DoubleStretchy(Source* s0, Source* s1);
  ~DoubleStretchy();

  virtual void initialize();

  virtual bool fillNext();
  virtual int available() const;
  virtual void setDescription(const TimeStretch& description);

  virtual int getTotalLength() const;
  virtual int getNextReadPosition() const;
  virtual void setNextReadPosition(int position);
  virtual void prepareToPlay(int s, double r);
  virtual void releaseResources();
  virtual void getNextAudioBlock(const juce::AudioSourceChannelInfo& info);
  virtual bool isLooping() const;
  virtual void setLooping(bool looping);

 private:
  bool descriptionChanged_;
  scoped_ptr<TimeStretch> description_;

  int position_;
  bool gettingBlock_;

  static const int BUFFER_COUNT = 2;
  scoped_ptr<BufferedStretchy> buffer0_;
  scoped_ptr<BufferedStretchy> buffer1_;

  BufferedStretchy* buffer_;
  BufferedStretchy* next_;
  CriticalSection lock_;

  DISALLOW_COPY_AND_ASSIGN(DoubleStretchy);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_DOUBLESTRETCHY__
