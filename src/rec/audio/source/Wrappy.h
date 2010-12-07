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

  void setSource(Source* source) { source_.reset(source); }
  Source* transfer() { return source_.transfer(); }

 protected:
  virtual Source* source() const { return source_.get(); }
  scoped_ptr<Source> source_;

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(Wrappy);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_WRAPPY__
