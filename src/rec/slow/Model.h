#ifndef __REC_SLOW_MODEL__
#define __REC_SLOW_MODEL__

#include "rec/audio/stretch/Stretch.pb.h"
#include "rec/audio/util/FileBuffer.h"
#include "rec/data/persist/Persist.h"
#include "rec/gui/audio/LoopPoint.pb.h"
#include "rec/slow/HasInstance.h"
#include "rec/util/Switcher.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/util/listener/Listener.h"
#include "rec/util/thread/Locker.h"

namespace rec {
namespace slow {

class Instance;

class Model : public Listener<const VirtualFile&>, public HasInstance {
 public:
  typedef audio::stretch::Stretch Stretch;
  typedef gui::audio::LoopPointList LoopPointList;

  explicit Model(Instance* i);

  void setVirtualFile(const VirtualFile&);

  thread::Locker<VirtualFile> fileLocker_;
  thread::Locker<Stretch> stretchLocker_;
  thread::Locker<LoopPointList> loopLocker_;

  Switcher<audio::util::FileBuffer> fileBuffer_;
  Thread* fetchThread_;
  CriticalSection lock_;

  virtual void operator()(const VirtualFile& vf) { fileLocker_.set(vf); }

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Model);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_MODEL__
