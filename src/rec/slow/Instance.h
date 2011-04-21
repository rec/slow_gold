#ifndef __REC_SLOW_INSTANCE__
#define __REC_SLOW_INSTANCE__

#include "rec/audio/Device.h"
#include "rec/audio/source/Player.h"
#include "rec/slow/Broadcasters.h"
#include "rec/slow/Components.h"
#include "rec/slow/Listeners.h"
#include "rec/slow/Menus.h"
#include "rec/slow/PersistentData.h"
#include "rec/slow/Target.h"
#include "rec/slow/Threads.h"

namespace rec {
namespace slow {

// A single instance of Slow.  Right now there's only one per application but in
// future there might be more than one.  This is where all the Broadcasters live
// and all the file and stretch setting persistent data, too.
struct Instance {
  typedef audio::source::Player Player;

  Instance();

  Broadcasters broadcasters_;
  Components components_;
  audio::Device device_;
  Listeners listeners_;
  Menus menus_;
  PersistentData data_;
  Player player_;
  Target target_;
  Threads threads_;

  DISALLOW_COPY_AND_ASSIGN(Instance);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_INSTANCE__
