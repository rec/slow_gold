#ifndef __REC_AUDIO_SOURCE_WRAPPY__
#define __REC_AUDIO_SOURCE_WRAPPY__

#include <vector>
#include <glog/logging.h>
#include "juce_amalgamated.h"

#include "rec/base/base.h"

namespace rec {
namespace audio {
namespace source {

template <typename Source>
class Wrappy : public PositionableAudioSource {
 public:
  Wrappy(Source* source) : source_(source) {}

  virtual void getNextAudioBlock(const AudioSourceChannelInfo& info) = 0;

  virtual int getTotalLength() const { return source_->getTotalLength(); }

  virtual int getNextReadPosition() const { return source_->getNextReadPosition(); }
  virtual void setNextReadPosition(int p) { source_->setNextReadPosition(p); }

  virtual bool isLooping() const { return source_->isLooping(); }
  virtual void setLooping(bool looping) { source_->setLooping(looping); }

  virtual void prepareToPlay(int s, double r) { source_->prepareToPlay(s, r);  }
  virtual void releaseResources() { source_->releaseResources(); }

 protected:
  Source* source_;

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(Wrappy);
};

template <typename Source>
class PositionWrappy : public Wrappy<Source> {
 public:
  PositionWrappy(Source* source) : Wrappy<Source>(source), position_(0) { }

  virtual int getNextReadPosition() const { return position_; }
  virtual void setNextReadPosition(int p) {
    Wrappy<Source>::setNextReadPosition(p);
    position_ = p;
  }

 protected:
  int position_;

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(PositionWrappy);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_WRAPPY__
