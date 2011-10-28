#ifndef __REC_SLOW_METHODS_FILEMETHODS__
#define __REC_SLOW_METHODS_FILEMETHODS__

#include "rec/slow/HasInstance.h"
#include "rec/util/listener/Listener.h"
#include "rec/util/file/VirtualFile.pb.h"

namespace rec {

namespace gui { class DropFiles; }

namespace slow {

class CurrentFile : public HasInstance,
                    public Listener<const VirtualFile&>,
                    public Listener<const gui::DropFiles&> {
 public:
  explicit CurrentFile(Instance* i) : HasInstance(i) {}

  virtual void operator()(const gui::DropFiles&);
  virtual void operator()(const VirtualFile&);

  const VirtualFile virtualFile() const { Lock l(lock_); return file_; }

 private:
  CriticalSection lock_;
  VirtualFile file_;
  DISALLOW_COPY_AND_ASSIGN(CurrentFile);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_METHODS_FILEMETHODS__
