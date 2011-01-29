#ifndef __REC_AUDIO_SOURCE_DOUBLESTRETCHYRUNNY__
#define __REC_AUDIO_SOURCE_DOUBLESTRETCHYRUNNY__

#include "rec/audio/source/DoubleRunny.h"
#include "rec/audio/stretch/Stretch.pb.h"
#include "rec/util/file/VirtualFile.h"

namespace rec {
namespace audio {
namespace source {

class DoubleStretchyRunny : public DoubleRunny {
 public:
  typedef stretch::StretchLoop StretchLoop;

  DoubleStretchyRunny(const VirtualFile& file,
                      const RunnyProto& desc = RunnyProto::default_instance());

  ~DoubleStretchyRunny();

  virtual void prepareToPlay(Runny* runny);
  void setStretchy(const StretchLoop& loop);

 protected:
  virtual PositionableAudioSource* makeSource() = 0;
  StretchLoop loop_;

  int64 nextRunnyPosition() const;

 private:
  const VirtualFile file_;
  double ratio_;
  double offset_;

  DISALLOW_COPY_AND_ASSIGN(DoubleStretchyRunny);
};


}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_DOUBLESTRETCHYRUNNY__
