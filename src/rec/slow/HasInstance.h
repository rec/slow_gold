#ifndef __REC_SLOW_HASINSTANCE__
#define __REC_SLOW_HASINSTANCE__

#include "rec/slow/Instance.h"

namespace rec {
namespace slow {

class HasInstance {
 public:
  HasInstance(Instance* i) : instance_(i) {}

  Components* components() { return instance_->components_.get(); }
  Listeners* listeners() { return instance_->listeners_.get(); }
  Target* target() { return instance_->target_.get(); }
  Threads* threads() { return instance_->threads_.get(); }
  audio::source::Player* player() { return instance_->player_.get(); }
  audio::Device* device() { return instance_->device_.get(); }

 protected:
  Instance* instance_;
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_HASINSTANCE__
