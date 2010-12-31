#ifndef __REC_AUDIO_SOURCE_DOUBLESTRETCHYRUNNY__
#define __REC_AUDIO_SOURCE_DOUBLESTRETCHYRUNNY__

#include "rec/audio/source/DoubleRunny.h"
#include "rec/audio/source/Stretchy.pb.h"
#include "rec/util/file/VolumeFile.h"

namespace rec {
namespace audio {
namespace source {

class DoubleStretchyRunny : public DoubleRunny {
 public:
  DoubleStretchyRunny(const VolumeFile& file,
                      const RunnyProto& desc = RunnyProto::default_instance());

  ~DoubleStretchyRunny();

  virtual void prepareNext(Runny* runny);
  void setStretchy(const StretchyProto& desc);

 protected:
  virtual PositionableAudioSource* makeSource() = 0;
  StretchyProto stretchyDesc_;

  int nextRunnyPosition() const;

 private:
  const VolumeFile file_;
  double ratio_;

  DISALLOW_COPY_AND_ASSIGN(DoubleStretchyRunny);
};


}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_DOUBLESTRETCHYRUNNY__
