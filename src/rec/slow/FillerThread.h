#ifndef __REC_SLOW_FILLERTHREAD__
#define __REC_SLOW_FILLERTHREAD__

#include "rec/slow/HasInstance.h"

namespace rec {
namespace slow {

class FillerThread : public HasInstance, public Thread {
 public:
  FillerThread(Instance* i) : HasInstance(i), Thread("Filler") {}

  virtual void run();

 private:
  void setFillPositionOrJump();

  DISALLOW_COPY_ASSIGN_AND_LEAKS(FillerThread);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_FILLERTHREAD__
