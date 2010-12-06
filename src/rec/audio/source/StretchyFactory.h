#ifndef __REC_AUDIO_SOURCE_STRETCHYFACTORY__
#define __REC_AUDIO_SOURCE_STRETCHYFACTORY__

#include "rec/audio/source/StretchyFactory.h"

#include "rec/util/thread/Factory.h"
#include "rec/widget/tree/VolumeFile.h"
#include "rec/widget/Panes.h"
#include "rec/slow/Preferences.h"

namespace rec {
namespace audio {
namespace source {

class Runny;

Runny* newRunny(const widget::pane::Track& track);
Runny* filledRunny(const widget::pane::Track& track, Thread* thread);

typedef util::thread::Factory<Runny*, const slow::proto::Preferences&> StretchyFactoryBase;

class StretchyFactory : public StretchyFactoryBase {
 public:
  StretchyFactory(Thread *thread = NULL) : thread_(thread) {}

  bool threadShouldExit() const { return thread_ && thread_->threadShouldExit(); }

  virtual Runny* makeProduct(const slow::proto::Preferences& track);

 private:
  Thread* thread_;
  DISALLOW_COPY_AND_ASSIGN(StretchyFactory);
};


}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_STRETCHYFACTORY__
