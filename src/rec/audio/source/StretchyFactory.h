#ifndef __REC_AUDIO_SOURCE_STRETCHYFACTORY__
#define __REC_AUDIO_SOURCE_STRETCHYFACTORY__

#include "rec/base/base.h"
#include "rec/util/thread/Factory.h"

namespace rec {
namespace audio {
namespace source {

class StretchyRunny : public Runny {
 public:
  explicit StretchyRunny(const StretchyRunnyDesc& desc)
      : Runny(desc.runny(), new Stretchy(desc.stretchy())) {
    while (!fill());
    startThread();
  }

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(StretchyRunny);
};

typedef util::thead::Factory<StretchyRunny, StretchyRunnyDesc> StretchyFactory;

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_STRETCHYFACTORY__
