#ifndef __REC_AUDIO_SOURCE_SWITCHING__
#define __REC_AUDIO_SOURCE_SWITCHING__

#include "rec/audio/source/Wrappy.h"
#include "rec/audio/source/ThreadedSource.h"
#include "rec/util/thread/Trash.h"

namespace rec {
namespace audio {
namespace source {

class Switching : public Wrappy {
 public:
  Switching();
  virtual ~Switching();

  virtual void shutdown();

  void setNextRunny(ThreadedSource* next);
  virtual void getNextAudioBlock(const AudioSourceChannelInfo& info);

 protected:
  virtual PositionableAudioSource* getSource() const { return runny_.get(); }

 private:
  thread_ptr<ThreadedSource> runny_, nextRunny_;

  DISALLOW_COPY_AND_ASSIGN(Switching);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_SWITCHING__
