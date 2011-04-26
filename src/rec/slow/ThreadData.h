#ifndef __REC_SLOW_THREADDATA__
#define __REC_SLOW_THREADDATA__

#include "rec/util/listener/Listener.h"
#include "rec/util/thread/Locker.h"
#include "rec/util/Switcher.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/audio/stretch/Stretch.pb.h"
#include "rec/audio/util/FileBuffer.h"

namespace rec {
namespace slow {

struct ThreadData : public Listener<const VirtualFile&>,
                    public Listener<const audio::stretch::StretchLoop&> {
  typedef audio::stretch::StretchLoop StretchLoop;

  ThreadData() : fileLocker_(&lock_), stretchLocker_(&lock_) {}

  virtual void operator()(const VirtualFile& vf) { fileLocker_.set(vf); }
  virtual void operator()(const StretchLoop& sl) { stretchLocker_.set(sl); }

  thread::Locker<VirtualFile> fileLocker_;
  thread::Locker<StretchLoop> stretchLocker_;

  Switcher<audio::util::FileBuffer> fileBuffer_;
  CriticalSection lock_;

  DISALLOW_COPY_AND_ASSIGN(ThreadData);
};

class Instance;

void updateParameters(Instance* i);

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_THREADDATA__
