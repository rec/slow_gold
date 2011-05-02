#ifndef __REC_SLOW_LISTENERS__
#define __REC_SLOW_LISTENERS__

#include "rec/audio/Audio.h"
#include "rec/command/Command.pb.h"
#include "rec/slow/HasInstance.h"
#include "rec/util/Range.h"
#include "rec/util/listener/Listener.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {

namespace audio { namespace stretch { class Stretch; }}
namespace gui { class DropFiles; }
namespace gui { namespace audio { class LoopPointList; }}

namespace util { class ClockUpdate; }
namespace util { namespace file { class VirtualFile; }}
namespace util { namespace file { class VirtualFileList; }}

namespace widget { namespace waveform { class CursorTime; }}
namespace widget { namespace waveform { class TimeAndMouseEvent; }}
namespace widget { namespace waveform { class ZoomProto; }}

namespace slow {

class ClockTick;
class Instance;

class Listeners : public Listener<None>,
                  public Listener<audio::transport::State>,
                  public Listener<command::Command::Type>,
                  public Listener<const audio::stretch::Stretch&>,
                  public Listener<const gui::DropFiles&>,
                  public Listener<const gui::audio::LoopPointList&>,
                  public juce::MouseListener,
                  public HasInstance {
 public:
  explicit Listeners(Instance* i);

  virtual void operator()(None);
  virtual void operator()(audio::transport::State);
  virtual void operator()(command::Command::Type);
  virtual void operator()(const audio::stretch::Stretch&);
  virtual void operator()(const gui::DropFiles&);
  virtual void operator()(const gui::audio::LoopPointList&);

  void operator()(const ClockTick&);
  void operator()(const ClockUpdate&);
  void operator()(const widget::waveform::CursorTime&);
  void operator()(const widget::waveform::TimeAndMouseEvent&);
  void operator()(const widget::waveform::ZoomProto&);
  void operator()(SampleTime) {}
  void operator()(RealTime);

  template <typename Type>
  void callAsync(Type t) {
    typedef void (Listeners::*Member)(Type);
    Member m = &Listeners::operator();
    thread::callAsync(this, m, t);
  }

  void mouseDoubleClick(const MouseEvent& e);
  void mouseUp(const MouseEvent& e);
  void mouseDrag(const MouseEvent& e);

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Listeners);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_LISTENERS__
