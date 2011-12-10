#ifndef __REC_SLOW_INSTANCE__
#define __REC_SLOW_INSTANCE__

#include "rec/base/Samples.h"

namespace rec {

namespace audio { class Device; }
namespace audio { namespace source { class Player; }}

namespace slow {

class BufferFiller;
class Components;
class CurrentFile;
class CurrentTime;
class GuiListener;
class Menus;
class MouseListener;
class SlowWindow;
class Target;
class Threads;

// A single instance of the Slow program.  Right now there's only one per
// application but in future there might be more than one.
class Instance {
 public:
  explicit Instance(SlowWindow* window);
  ~Instance();

  void startup();
  const VirtualFile file() const;
  Samples<44100> time() const;
  Samples<44100> length() const;
  bool isPlaying() const;
  void updateGui();

  SlowWindow* window_;

  ptr<Menus> menus_;
  ptr<audio::Device> device_;
  ptr<BufferFiller> bufferFiller_;
  ptr<CurrentFile> currentFile_;

  ptr<audio::source::Player> player_;
  ptr<Components> components_;
  ptr<CurrentTime> currentTime_;

  ptr<Target> target_;
  ptr<MouseListener> mouseListener_;
  ptr<GuiListener> guiListener_;
  ptr<Threads> threads_;

 private:
  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(Instance);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_INSTANCE__
