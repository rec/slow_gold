#ifndef __REC_SLOW_FILLERTHREAD__
#define __REC_SLOW_FILLERTHREAD__

#include "rec/base/base.h"

namespace rec {
namespace slow {

class FillerThread : public Thread {
 public:
  FillerThread() : Thread("Filler") {}
  virtual void run();

 private:
  void setFillPositionOrJump();

  DISALLOW_COPY_ASSIGN_AND_LEAKS(FillerThread);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_FILLERTHREAD__
