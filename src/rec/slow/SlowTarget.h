#ifndef __REC_SLOW_SLOWTARGET__
#define __REC_SLOW_SLOWTARGET__

#include "rec/command/Target.h"
#include "rec/command/Instance.h"
#include "rec/command/Command.pb.h"

namespace rec {
namespace slow {

class SlowTarget : public command::Target {
 public:
  SlowTarget(Instance* instance, MainPage* mp, ComponentContainer* cc);
  virtual ~SlowTarget() {}

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(SlowTarget);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_SLOWTARGET__
