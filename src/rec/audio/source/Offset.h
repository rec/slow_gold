#ifndef __REC_AUDIO_SOURCE_OFFSET__
#define __REC_AUDIO_SOURCE_OFFSET__

#include "rec/base/basictypes.h"

namespace rec {
namespace audio {
namespace source {

// Wrap a Source with an offset, measured in integer samples.
class Offset : public Wrappy {
 public:
  Offset(Source* source, int offset) : Wrappy(source), offset_(offset) {}

  virtual int getNextReadPosition() const {
    return mod(source_->getNextReadPosition() + offset_);
  }

  virtual void setNextReadPosition(int position) {
    source_->setNextReadPosition(mod(position - offset_));
  }

  int offset() const { return offset_; }
  void setOffset(int offset) { offset_ = offset; }

 private:
  int offset_;
  DISALLOW_COPY_ASSIGN_AND_EMPTY(Offset);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_OFFSET__
