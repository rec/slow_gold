#ifndef __REC_AUDIO_SOURCE_WRAPPY__
#define __REC_AUDIO_SOURCE_WRAPPY__

#include <vector>

#include "rec/audio/source/Source.h"
#include "rec/audio/source/Empty.h"
#include "rec/util/Math.h"

namespace rec {
namespace audio {
namespace source {

class Wrappy : public PositionableAudioSource {
 public:
  Wrappy(Source* source = NULL) { setSource(source); }

  // TODO:  no longer used?
  virtual void getNextAudioBlock(const juce::AudioSourceChannelInfo& info) {
    source()->getNextAudioBlock(info);
  }

  virtual int getTotalLength() const { return source()->getTotalLength(); }

  virtual int getNextReadPosition() const {
    return source()->getNextReadPosition();
  }

  virtual void setNextReadPosition(int p) { source()->setNextReadPosition(p); }

  virtual bool isLooping() const { return source()->isLooping(); }
  virtual void setLooping(bool looping) { source()->setLooping(looping); }

  virtual void prepareToPlay(int s, double r) { source()->prepareToPlay(s, r);  }
  virtual void releaseResources() { source()->releaseResources(); }

  int mod(int x) const { return util::mod(x, getTotalLength()); }

  void advance(int x) {
    setNextReadPosition(mod(x + getNextReadPosition()));
  }

  virtual PositionableAudioSource* source() const { 
    return source_.get(); 
  }
  void setSource(PositionableAudioSource* s = NULL) { 
    source_.reset(s ? s : new Empty()); 
  }
  PositionableAudioSource* transfer() { 
    return source_.transfer(); 
  }

  class Position;

 private:
  ptr<Source> source_;
  DISALLOW_COPY_ASSIGN_AND_EMPTY(Wrappy);
};

// A Source with an embedded Position.
class Wrappy::Position : public Wrappy {
 public:
  Position(Source* source, int pos = 0) : Wrappy(source), position_(pos) {}

  virtual int getNextReadPosition() const {
    ScopedLock l(lock_);
    return position_;
  }

  virtual void setNextReadPosition(int p) {
    source()->setNextReadPosition(p);
    ScopedLock l(lock_);
    position_ = p;
  }

  virtual void getNextAudioBlock(const juce::AudioSourceChannelInfo& info) {
    source()->getNextAudioBlock(info);

    ScopedLock l(lock_);
    position_ = mod(position_ + info.numSamples);
  }

 protected:
  CriticalSection lock_;
  int position_;

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(Position);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_WRAPPY__
