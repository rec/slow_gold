#ifndef __REC_PERSIST_WRITEABLE__
#define __REC_PERSIST_WRITEABLE__

#include "rec/base/base.h"
#include "JuceLibraryCode/JuceHeader.h"

namespace rec {
namespace persist {

class Writeable {
 public:
  Writeable() {}
  virtual ~Writeable() {}

  virtual void write() {
    ScopedLock l(lock_);
    if (changed_) {
      doWrite();
      changed_ = false;
    }
  }

 protected:
  virtual void doWrite() = 0;

  CriticalSection lock_;
  bool changed_;

 private:
  DISALLOW_COPY_AND_ASSIGN(Writeable);
};

}  // namespace persist
}  // namespace rec

#endif  // __REC_PERSIST_WRITEABLE__
