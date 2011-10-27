#ifndef __REC_SLOW_INSTANCE__
#define __REC_SLOW_INSTANCE__

#include "rec/slow/Slow.h"
#include "rec/base/Samples.h"

namespace rec {
namespace slow {

class Components;
class CurrentFile;
class CurrentTime;
class Menus;
class BufferFiller;
class MouseListener;
class Target;
class Threads;
class SlowWindow;

// A single instance of Slow.  Right now there's only one per application but in
// future there might be more than one.  This is where all the Broadcasters live
// and all the file and stretch setting persistent data, too.
struct Instance {
  explicit Instance(SlowWindow* window);
  ~Instance();

  void startup();
  const VirtualFile file() const;
  Samples<44100> length() const;
  Samples<44100> time() const;

  SlowWindow* window_;

  ptr<Components> components_;
  ptr<Device> device_;
  ptr<Player> player_;
  ptr<CurrentFile> currentFile_;
  ptr<CurrentTime> currentTime_;
  ptr<BufferFiller> bufferFiller_;
  ptr<Menus> menus_;  // TODO:  move into "Target"
  ptr<Target> target_;  // TODO: rename to "Commands".
  ptr<MouseListener> mouseListener_;
  ptr<Threads> threads_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Instance);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_INSTANCE__
