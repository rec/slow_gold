#ifndef __REC_AUDIO_SOURCE_WRAPPY__
#define __REC_AUDIO_SOURCE_WRAPPY__

#include <vector>
#include <glog/logging.h>

#include "rec/audio/source/Source.h"
#include "rec/util/Math.h"

namespace rec {
namespace audio {
namespace source {

class Wrappy : public Source {
 public:
  Wrappy(Source* source) : source_(source) {}
  virtual void initialize() {}

  virtual void getNextAudioBlock(const juce::AudioSourceChannelInfo& info) {
    source_->getNextAudioBlock(info);
  }

  virtual int getTotalLength() const { return source_->getTotalLength(); }

  virtual int getNextReadPosition() const {
    return source_->getNextReadPosition();
  }

  virtual void setNextReadPosition(int p) { source_->setNextReadPosition(p); }

  virtual bool isLooping() const { return source_->isLooping(); }
  virtual void setLooping(bool looping) { source_->setLooping(looping); }

  virtual void prepareToPlay(int s, double r) { source_->prepareToPlay(s, r);  }
  virtual void releaseResources() { source_->releaseResources(); }

  int mod(int x) const { return util::mod(x, getTotalLength()); }

  void advance(int x) {
    setNextReadPosition(mod(x + getNextReadPosition()));
  }

  class Position;

 protected:
  Source* source_;

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(Wrappy);
};

// A Source with an embedded Position.  Probably we should be
// using this less and relying more on the contained class's position_.
class Wrappy::Position : public Wrappy {
 public:
  Position(Source* source, int position = 0)
      : Wrappy(source), position_(position) {
  }

  virtual int getNextReadPosition() const { return position_; }
  virtual void setNextReadPosition(int p) {
    source_->setNextReadPosition(p);
    position_ = p;
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
