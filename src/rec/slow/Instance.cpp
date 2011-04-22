#include "rec/slow/Instance.h"
#include "rec/util/thread/Trash.h"

namespace rec {
namespace slow {

Instance::Instance() : components_(this), menus_(this), player_(&device_),
                       target_(this), threads_(this), listeners_(this) {
}

}  // namespace slow
}  // namespace rec
