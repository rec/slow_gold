#ifndef __REC_CRITICAL_SECTION
#define __REC_CRITICAL_SECTION

#include "rec/util/locker.h"

namespace rec {
namespace util {

class CriticalSectionLock : public LockInterface {
 private:
  CriticalSection lock_;

 public:
  void enter() { lock_.enter(); }
  void exit() { lock_.exit(); }
};


}  // namespace util
}  // namespace rec


#endif  // __REC_CRITICAL_SECTION
