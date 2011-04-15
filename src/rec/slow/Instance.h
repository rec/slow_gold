#ifndef __REC_SLOW_INSTANCE__
#define __REC_SLOW_INSTANCE__

#include "rec/audio/Device.h"
#include "rec/audio/source/Player.h"
#include "rec/slow/Broadcasters.h"
#include "rec/slow/Listeners.h"
#include "rec/slow/PersistentData.h"

namespace rec {
namespace app {

// A single instance of Slow.  Right now there's only one per application but in
// future there might be more than one.  This is where all the Broadcasters live
// and all the file and stretch setting persistent data, too.
struct Instance {
  typedef audio::source::Player Player;

  explicit Instance(Listeners* l, Player* p) : listeners_(l), player_(p) {
    player_->addListener(*listeners_);  TODO
  }

  Listeners* listeners_;
  Player* player_;

  PersistentData data_;
  Broadcasters broadcasters_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Instance);
};

}  // namespace app
}  // namespace rec

#endif  // __REC_SLOW_INSTANCE__
