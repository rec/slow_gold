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
  Wrappy(PositionableAudioSource* s = NULL) { setSource(s); }

  // TODO:  no longer used?
  virtual void getNextAudioBlock(const AudioSourceChannelInfo& i) {
    source()->getNextAudioBlock(i);
  }

  virtual int getTotalLength() const { return source()->getTotalLength(); }

  virtual int getNextReadPosition() const { return source()->getNextReadPosition(); }

  virtual void setNextReadPosition(int p) { source()->setNextReadPosition(p); }

  virtual bool isLooping() const { return source()->isLooping(); }
  virtual void setLooping(bool looping) { source()->setLooping(looping); }

  virtual void prepareToPlay(int s, double r) { source()->prepareToPlay(s, r);  }
  virtual void releaseResources() { source()->releaseResources(); }

  int mod(int x) const { return util::mod(x, getTotalLength()); }

  virtual PositionableAudioSource* source() const {
    ScopedLock l(lock_);
    if (PositionableAudioSource* source = getSource())
      return source;

    static Empty empty;
    return &empty;
  }

  void setSource(PositionableAudioSource* s) {
    ScopedLock l(lock_);
    source_.reset(s);
  }

  class Position;

 protected:
  virtual PositionableAudioSource* getSource() const { return source_.get(); }

  CriticalSection lock_;

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
    ScopedLock l(lock_);
    source()->setNextReadPosition(p);
    position_ = p;
  }

  virtual void getNextAudioBlock(const juce::AudioSourceChannelInfo& info) {
    source()->getNextAudioBlock(info);

    ScopedLock l(lock_);
    position_ = mod(position_ + info.numSamples);
  }

 protected:
  int position_;

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(Position);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_WRAPPY__
