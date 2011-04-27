#ifndef __REC_SLOW_THREADDATA__
#define __REC_SLOW_THREADDATA__

#include "rec/util/listener/Listener.h"
#include "rec/util/thread/Locker.h"
#include "rec/util/Switcher.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/audio/stretch/Stretch.pb.h"
#include "rec/audio/util/FileBuffer.h"
#include "rec/data/persist/Persist.h"

namespace rec {
namespace slow {

struct ThreadData : public Listener<const VirtualFile&>,
                    public Listener<const audio::stretch::Stretch&> {
  typedef audio::stretch::Stretch Stretch;

  ThreadData() : fileLocker_(&lock_), stretchLocker_(&lock_),
                 fetchThread_(NULL) {
    persist::appData<VirtualFile>()->addListener(this);
  }

  thread::Locker<VirtualFile> fileLocker_;
  thread::Locker<Stretch> stretchLocker_;

  Switcher<audio::util::FileBuffer> fileBuffer_;
  Thread* fetchThread_;
  CriticalSection lock_;

  virtual void operator()(const VirtualFile& vf) {
    fileLocker_.set(vf);
  }
  virtual void operator()(const Stretch& sl) { stretchLocker_.set(sl); }

  DISALLOW_COPY_AND_ASSIGN(ThreadData);
};

class Instance;

void updateParameters(Instance* i);

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_THREADDATA__
