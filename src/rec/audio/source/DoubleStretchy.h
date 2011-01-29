#ifndef __REC_AUDIO_SOURCE_DOUBLESTRETCHYRUNNY__
#define __REC_AUDIO_SOURCE_DOUBLESTRETCHYRUNNY__

#include "rec/audio/source/DoubleRunny.h"
#include "rec/audio/source/Stretchy.h"
#include "rec/util/file/VirtualFile.h"

namespace rec {
namespace audio {
namespace source {

class DoubleStretchy : public DoubleRunny {
 public:
  DoubleStretchy(const VirtualFile& file,
                 const RunnyProto& desc = RunnyProto::default_instance());

  ~DoubleStretchy();

  virtual void prepareToPlay(Runny* runny);
  void setLoop(const StretchLoop& loop, int pos);
  int64 setLoopPosition(const StretchLoop& loop);

 protected:
  virtual PositionableAudioSource* makeSource() = 0;
  StretchLoop loop_;

  int64 nextRunnyPosition() const;

 private:
  const VirtualFile file_;
  double ratio_;
  double offset_;

  DISALLOW_COPY_AND_ASSIGN(DoubleStretchy);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_DOUBLESTRETCHYRUNNY__
