#ifndef __REC_AUDIO_SOURCE_WRAPPER_H__
#define __REC_AUDIO_SOURCE_WRAPPER_H__

#include "JuceLibraryCode/JuceHeader.h"
#include "rec/audio/source/Source.h"

namespace rec {
namespace audio {
namespace source {

// Delegate to another Source.
class Wrapper : public Source {
 public:
  Wrapper(Source* s) : source_(s) { jassert(s); }

  virtual void prepareToPlay(int samples, double rate) {
    source_->prepareToPlay(samples, rate);
  }
  virtual void releaseResources() {
    source_->releaseResources();
  }
  virtual void getNextAudioBlock (const AudioSourceChannelInfo& blockInfo) {
    source_->getNextAudioBlock(blockInfo);
  }
  virtual void setNextReadPosition(int p) {
    source_->setNextReadPosition(p);
  }
  virtual int getNextReadPosition() const {
    return source_->getNextReadPosition();
  }
  virtual int getTotalLength() const {
    return source_->getTotalLength();
  }
  virtual bool isLooping() const {
    return source_->isLooping();
  }

 protected:
  scoped_ptr<Source> source_;

  DISALLOW_COPY_AND_ASSIGN(Wrapper);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_WRAPPER_H__
