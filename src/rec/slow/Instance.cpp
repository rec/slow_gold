#include "rec/slow/Instance.h"
#include "rec/util/thread/Trash.h"

namespace rec {
namespace slow {

Instance::Instance() : player_(&device_), components_(this), listeners_(this),
                       menus_(this), threads_(this) {
  player_->addListener(listeners_.transportState_);

}

}  // namespace slow
}  // namespace rec
