#ifndef __REC_AUDIO_SOURCE_DOUBLERUNNY__
#define __REC_AUDIO_SOURCE_DOUBLERUNNY__

#include "rec/audio/source/Wrappy.h"
#include "rec/audio/source/Runny.h"
#include "rec/audio/source/Stretchy.pb.h"
#include "rec/util/listener/Broadcaster.h"
#include "rec/util/listener/Listener.h"
#include "rec/util/thread/ChangeLocker.h"

namespace rec {
namespace audio {
namespace source {

class StretchyProto;

class DoubleRunny : public Wrappy {
 public:
  DoubleRunny(const VolumeFile& file,
              const RunnyProto& desc = RunnyProto::default_instance());

  ~DoubleRunny();

  void setStretchy(const StretchyProto& desc);
  virtual void getNextAudioBlock(const AudioSourceChannelInfo& info);

 protected:
  virtual PositionableAudioSource* makeSource();
  virtual Source* source() const;
  StretchyProto stretchyDesc_;

 private:
  const VolumeFile file_;
  const RunnyProto runnyDesc_;

  CriticalSection lock_;
  ptr<Runny> runny_, nextRunny_;
  double ratio_;

  DISALLOW_COPY_AND_ASSIGN(DoubleRunny);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_DOUBLERUNNY__
