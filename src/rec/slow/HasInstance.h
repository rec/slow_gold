#ifndef __REC_SLOW_HASINSTANCE__
#define __REC_SLOW_HASINSTANCE__

#include "rec/slow/Instance.h"
#include "rec/util/file/VirtualFile.pb.h"
#include "rec/util/LoopPoint.pb.h"

namespace rec {
namespace slow {

class HasInstance {
 public:
  explicit HasInstance(Instance* i = nullptr) {}

 private:
  DISALLOW_COPY_ASSIGN_AND_LEAKS(HasInstance);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_HASINSTANCE__
