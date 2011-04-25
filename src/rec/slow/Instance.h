#ifndef __REC_SLOW_INSTANCE__
#define __REC_SLOW_INSTANCE__

#include "rec/base/base.h"

namespace rec {
namespace audio {

class Device;

namespace source {

class Player;

}   // namespace source
}   // namespace audio

namespace slow {

class Components;
class Menus;
class PersistentData;
class Player;
class Target;
class Threads;
class Listeners;

// A single instance of Slow.  Right now there's only one per application but in
// future there might be more than one.  This is where all the Broadcasters live
// and all the file and stretch setting persistent data, too.
struct Instance {
  typedef audio::source::Player Player;

  Instance();
  ~Instance();

  // ptr<Broadcasters> broadcasters_;
  ptr<Components> components_;
  ptr<audio::Device> device_;
  ptr<Menus> menus_;
  ptr<PersistentData> data_;
  ptr<Player> player_;
  ptr<Target> target_;
  ptr<Listeners> listeners_;
  ptr<Threads> threads_;

  DISALLOW_COPY_AND_ASSIGN(Instance);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_INSTANCE__
