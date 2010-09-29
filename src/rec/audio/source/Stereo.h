#ifndef __REC_AUDIO_SOURCE_STEREO__
#define __REC_AUDIO_SOURCE_STEREO__

#include "rec/base/base.h"
#include "rec/audio/source/Wrappy.h"

namespace rec {
namespace audio {
namespace source {

class Stereo : public Wrappy {
 public:
  enum Type {
    PASSTHROUGH,
    SINGLE,
    INVERT,
    CENTER_ELIMINATION,
    CENTER_ELIMINATION_MONO
  };

  enum Side { LEFT, RIGHT };

  Stereo(Source* source) : Wrappy(source), type_(PASSTHROUGH), side_(LEFT) {}

  void setType(Type type);
  void setSide(Side side);
  virtual void getNextAudioBlock(const AudioSourceChannelInfo& info);

 private:
  Type type_;
  Side side_;
  CriticalSection lock_;

  DISALLOW_COPY_AND_ASSIGN(Stereo);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_STEREO__
