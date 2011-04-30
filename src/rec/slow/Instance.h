#ifndef __REC_SLOW_INSTANCE__
#define __REC_SLOW_INSTANCE__

#include "rec/base/base.h"

namespace rec { namespace audio { class Device; }}
namespace rec { namespace audio { namespace source { class Player; }}}

namespace rec {
namespace slow {

class Components;
class Menus;
class Parameters;
class PersistentData;
class Target;
class Threads;
class Listeners;

// A single instance of Slow.  Right now there's only one per application but in
// future there might be more than one.  This is where all the Broadcasters live
// and all the file and stretch setting persistent data, too.
struct Instance {
  Instance();
  ~Instance();

  ptr<Components> components_;
  ptr<audio::Device> device_;
  ptr<Menus> menus_;  // TODO:  move into "Target"
  ptr<audio::source::Player> player_;
  ptr<Target> target_;  // TODO: rename to "Commands".
  ptr<Listeners> listeners_;
  ptr<Threads> threads_;

  // ptr<PersistentData> data_;  // TODO:  delete this?
  // ptr<Parameters> parameters_;

  DISALLOW_COPY_AND_ASSIGN(Instance);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_INSTANCE__
