#ifndef __REC_AUDIO_SOURCE_DOUBLERUNNY__
#define __REC_AUDIO_SOURCE_DOUBLERUNNY__

#include "rec/audio/source/Wrappy.h"
#include "rec/audio/source/Runny.h"
#include "rec/util/thread/Trash.h"

namespace rec {
namespace audio {
namespace source {

class DoubleRunny : public Wrappy {
 public:
  DoubleRunny(const RunnyProto& proto = RunnyProto::default_instance());
  virtual ~DoubleRunny();

  virtual void shutdown();

  void setNextRunny(Runny* next);
  virtual void getNextAudioBlock(const AudioSourceChannelInfo& info);

 protected:
  virtual PositionableAudioSource* getSource() const { return runny_.get(); }

 private:
  thread_ptr<Runny> runny_, nextRunny_;
  RunnyProto runnyDesc_;

  DISALLOW_COPY_AND_ASSIGN(DoubleRunny);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_DOUBLERUNNY__
