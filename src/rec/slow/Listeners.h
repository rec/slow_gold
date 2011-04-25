#ifndef __REC_SLOW_LISTENERS__
#define __REC_SLOW_LISTENERS__

#include "rec/audio/Audio.h"
#include "rec/util/Range.h"
#include "rec/util/listener/Listener.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {

namespace audio {
namespace stretch {
class StretchLoop;
}  // namespace stretch
}  // namespace audio

namespace gui {
class DropFiles;
namespace audio {
class LoopPointList;
}  // namespace audio
}  // namespace gui

namespace util {
class ClockUpdate;

namespace file {
class VirtualFile;
class VirtualFileList;
}  // namespace file
}  // namespace util

namespace widget {
namespace waveform {
class CursorTime;
class TimeAndMouseEvent;
class ZoomProto;
}  // namespace waveform
}  // namespace widget

namespace slow {

class ClockTick;
class Instance;

class Listeners :
    public Listener<const juce::AudioThumbnail&>,
    public Listener<const ClockTick&>,
    public Listener<const ClockUpdate&>,
    public Listener<const SelectionRange&>,
    public Listener<const audio::stretch::StretchLoop&>,
    public Listener<const file::VirtualFile&>,
    public Listener<const file::VirtualFileList&>,
    public Listener<const gui::DropFiles&>,
    public Listener<const gui::audio::LoopPointList&>,
    public Listener<const widget::waveform::CursorTime&>,
    public Listener<const widget::waveform::TimeAndMouseEvent&>,
    public Listener<const widget::waveform::ZoomProto&>,
    public Listener<RealTime>,
    public Listener<audio::transport::State> {
 public:
  explicit Listeners(Instance* i);

  virtual void operator()(const ClockTick&);
  virtual void operator()(const juce::AudioThumbnail&);
  virtual void operator()(const ClockUpdate&);
  virtual void operator()(const SelectionRange&);
  virtual void operator()(const audio::stretch::StretchLoop&);
  virtual void operator()(const file::VirtualFile&);
  virtual void operator()(const file::VirtualFileList&);
  virtual void operator()(const gui::DropFiles&);
  virtual void operator()(const gui::audio::LoopPointList&);
  virtual void operator()(const widget::waveform::CursorTime&);
  virtual void operator()(const widget::waveform::TimeAndMouseEvent&);
  virtual void operator()(const widget::waveform::ZoomProto&);
  virtual void operator()(RealTime);
  virtual void operator()(audio::transport::State);

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
