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

class Components;
class CurrentFile;
class CurrentTime;
class Menus;
class BufferFiller;
class MouseListener;
class Target;
class Threads;
class SlowWindow;

typedef audio::source::Player Player;

typedef widget::waveform::Waveform Waveform;
typedef widget::waveform::WaveformProto WaveformProto;
typedef widget::waveform::ZoomProto ZoomProto;

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
  ptr<audio::Device> device_;
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
