#ifndef __REC_SLOW_SLOWLISTENERS__
#define __REC_SLOW_SLOWLISTENERS__

#include "rec/slow/Listeners.h"

namespace rec {
namespace slow {

class SlowListeners : public Listeners {
 public:
  SlowListeners() {}

  void setInstance(Instance* i) { instance_ = i; }

 private:
  Instance* instance_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(SlowListeners);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_SLOWLISTENERS__
