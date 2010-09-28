#ifndef __REC_AUDIO_SOURCE_DOUBLESTRETCHY__
#define __REC_AUDIO_SOURCE_DOUBLESTRETCHY__

// Wrap an incoming AudioSource, and time-stretch it.

#include "rec/audio/stretch/TimeStretch.pb.h"
#include "rec/audio/source/Wrappy.h"
#include "rec/audio/source/Buffery.h"
#include "rec/audio/source/Stretchy.h"
#include "rec/audio/stretch/TimeScaler.h"
#include "rec/base/scoped_ptr.h"

namespace rec {
namespace audio {
namespace source {

class BufferedStretchy : public Buffery {
 public:
  typedef timescaler::TimeStretch TimeStretch;
  BufferedStretchy(Source* s) : Buffery(&stretchy_), stretchy_(s) {}

  void setDescription(const TimeStretch& t, int position) {
    stretchy_.setDescription(t);
    resetFrom(t.channels(), position);
    setNextReadPosition(position);
  }

  const TimeStretch& getDescription() const {
    return stretchy_.getDescription();
  }

 private:
  Stretchy stretchy_;
  DISALLOW_COPY_ASSIGN_AND_EMPTY(BufferedStretchy);
};


class DoubleStretchy : public Source {
 public:
  typedef timescaler::TimeStretch TimeStretch;
  const static int MINIMUM_FILL_SIZE = 4096;

  DoubleStretchy(Source* s0, Source* s1);
  ~DoubleStretchy();

  virtual bool fillNext();
  virtual int available() const;
  virtual void setDescription(const TimeStretch& description);

  virtual int getTotalLength() const;
  virtual int getNextReadPosition() const;
  virtual void setNextReadPosition(int position);
  virtual void prepareToPlay(int s, double r);
  virtual void releaseResources();
  virtual void getNextAudioBlock(const AudioSourceChannelInfo& info);
  virtual bool isLooping() const;
  virtual void setLooping(bool looping);

 private:
  bool descriptionChanged_;
  TimeStretch description_;

  int position_;
  bool gettingBlock_;

  static const int BUFFER_COUNT = 2;
  BufferedStretchy buffer0_;
  BufferedStretchy buffer1_;

  BufferedStretchy* buffer_;
  BufferedStretchy* next_;
  CriticalSection lock_;

  DISALLOW_COPY_AND_ASSIGN(DoubleStretchy);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_DOUBLESTRETCHY__
