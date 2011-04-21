#ifndef __REC_SLOW_SLOWTARGET__
#define __REC_SLOW_SLOWTARGET__

#include "rec/command/Command.pb.h"
#include "rec/command/TargetManager.h"

namespace rec {
namespace slow {

class Instance;

class Target : public command::TargetManager {
 public:
  Target(Instance* instance, MainPage* mp, ComponentContainer* cc);
  virtual ~Target() {}

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(Target);
};

}  // namespace rec
}  // namespace slow

#endif  // __REC_SLOW_SLOWTARGET__
