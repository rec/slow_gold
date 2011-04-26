#ifndef __REC_SLOW_PARAMETERTHREAD__
#define __REC_SLOW_PARAMETERTHREAD__

#include "rec/util/listener/Listener.h"
#include "rec/util/thread/Locker.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/audio/stretch/Stretch.pb.h"

namespace rec {
namespace slow {

class ParameterUpdater : public Listener<const VirtualFile&>,
                         public Listener<const audio::stretch::StretchLoop&> {
 public:
  typedef audio::stretch::StretchLoop StretchLoop;

  ParameterUpdater() : fileLocker_(&lock_), stretchLocker_(&lock_) {}

  thread::Locker<VirtualFile>* file() { return &fileLocker_; }
  thread::Locker<StretchLoop>* stretch() { return &stretchLocker_; }

  virtual void operator()(const VirtualFile& vf) { fileLocker_.set(vf); }
  virtual void operator()(const StretchLoop& sl) { stretchLocker_.set(sl); }

 private:
  thread::Locker<VirtualFile> fileLocker_;
  thread::Locker<StretchLoop> stretchLocker_;
  CriticalSection lock_;

  DISALLOW_COPY_AND_ASSIGN(ParameterUpdater);
};

class Instance;

void updateParameters(Instance* i);

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_PARAMETERTHREAD__
