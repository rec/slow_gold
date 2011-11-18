#ifndef __REC_SLOW_INSTANCE__
#define __REC_SLOW_INSTANCE__

#include "rec/base/Samples.h"

namespace rec {

namespace audio { class Device; }
namespace audio { namespace source { class Player; }}
namespace widget { namespace waveform { class Waveform; }}
namespace widget { namespace waveform { class WaveformProto; }}
namespace widget { namespace waveform { class ZoomProto; }}

namespace slow {

class BufferFiller;
class Components;
class CurrentFile;
class CurrentTime;
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

  SlowWindow* window_;

  ptr<Menus> menus_;
  ptr<Components> components_;
  ptr<audio::Device> device_;
  ptr<audio::source::Player> player_;

  ptr<CurrentFile> currentFile_;
  ptr<CurrentTime> currentTime_;
  ptr<BufferFiller> bufferFiller_;

  ptr<Target> target_;
  ptr<MouseListener> mouseListener_;
  ptr<Threads> threads_;

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(Instance);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_INSTANCE__
