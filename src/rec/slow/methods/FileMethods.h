#ifndef __REC_SLOW_METHODS_FILEMETHODS__
#define __REC_SLOW_METHODS_FILEMETHODS__

#include "rec/slow/HasInstance.h"

namespace rec {

namespace gui {class DropFiles; }

namespace slow {
namespace methods {

class FileMethods : public HasInstance {
 public:
  explicit FileMethods(Instance* i) : HasInstance(i) {}

  void dropFiles(const gui::DropFiles&);
  void setFile(const VirtualFile& f, const VirtualFile& oldFile);

 private:
  DISALLOW_COPY_AND_ASSIGN(FileMethods);
};

}  // namespace methods
}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_METHODS_FILEMETHODS__
