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
  DoubleStretchy(const VirtualFile& file, const RunnyProto& desc);
  ~DoubleStretchy();

  virtual void prepareRunnyToPlay(Runny* runny);
  void setLoopPosition(const stretch::StretchLoop& loop);

 protected:
  stretch::StretchLoop loop_;

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
