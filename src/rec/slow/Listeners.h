#ifndef __REC_SLOW_LISTENERS__
#define __REC_SLOW_LISTENERS__

#include "rec/audio/Audio.h"
#include "rec/util/Range.h"
#include "rec/util/listener/Listener.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {

namespace audio { namespace stretch { class StretchLoop; }}
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
                  public Listener<const gui::DropFiles&>,
                  public Listener<audio::transport::State> {
 public:
  explicit Listeners(Instance* i);

  virtual void operator()(audio::transport::State);
  virtual void operator()(const gui::DropFiles&);
  virtual void operator()(None);

  void operator()(const ClockTick&);
  void operator()(juce::AudioThumbnail*);
  void operator()(const ClockUpdate&);
  void operator()(const SelectionRange&);
  void operator()(const audio::stretch::StretchLoop&);
  void operator()(const file::VirtualFile&);
  void operator()(const file::VirtualFileList&);
  void operator()(const gui::audio::LoopPointList&);
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

 private:
  Instance* instance_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Listeners);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_LISTENERS__
