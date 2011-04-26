#ifndef __REC_SLOW_PARAMETERTHREAD__
#define __REC_SLOW_PARAMETERTHREAD__

#include "rec/util/thread/Locker.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/audio/stretch/Stretch.pb.h"

namespace rec {
namespace slow {

struct ParameterUpdater {
  ParameterUpdater() : fileLocker_(&lock_), stretchLocker_(&lock_) {}

  thread::Locker<VirtualFile> fileLocker_;
  thread::Locker<audio::stretch::StretchLoop> stretchLocker_;
  CriticalSection lock_;

  DISALLOW_COPY_AND_ASSIGN(ParameterUpdater);
};

class Instance; 

void updateParameters(Instance* i);

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_PARAMETERTHREAD__
