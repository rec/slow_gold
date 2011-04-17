#ifndef __REC_SLOW_INSTANCE__
#define __REC_SLOW_INSTANCE__

#include "rec/audio/Device.h"
#include "rec/audio/source/Player.h"
// #include "rec/slow/Broadcasters.h"
#include "rec/slow/Components.h"
#include "rec/slow/Listeners.h"
#include "rec/slow/Menus.h"
#include "rec/slow/PersistentData.h"
#include "rec/slow/Target.h"

namespace rec {
namespace app {

// A single instance of Slow.  Right now there's only one per application but in
// future there might be more than one.  This is where all the Broadcasters live
// and all the file and stretch setting persistent data, too.
struct Instance {
  typedef audio::source::Player Player;

  explicit Instance() : player_(&device_), components_(this), listeners_(this),
                        menus_(this) {
    player_->addListener(listeners_.transportState_);
  }

  Device device_;
  Player player_;
  Components components_;
  Listeners listeners_;
  Target target_;
  Menus menus_;
  // Broadcasters broadcasters_;
  PersistentData data_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Instance);
};

}  // namespace app
}  // namespace rec

#endif  // __REC_SLOW_INSTANCE__
