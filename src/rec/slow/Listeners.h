#ifndef __REC_SLOW_LISTENERS__
#define __REC_SLOW_LISTENERS__

#include "rec/util/Listener.h"

namespace rec {
namespace slow {

class Listeners :
    public Listener<const ClockUpdate&>,
    public Listener<const SelectionRange&>,
    public Listener<const audio::stretch::StretchLoop&>,
    public Listener<const file::VirtualFile&>,
    public Listener<const file::VirtualFileList&>,
    public Listener<const gui::LoopPointList&>,
    public Listener<const widget::waveform::CursorTime&>,
    public Listener<const widget::waveform::TimeAndMouseEvent&>,
    public Listener<const widget::waveform::ZoomProto&>,
    public Listener<RealTime>,
    public Listener<TransportState> {
 public:
  explicit Listeners(Instance* i) : instance_(i) {}

  virtual void operator()(const ClockUpdate&);
  virtual void operator()(const SelectionRange&);
  virtual void operator()(const audio::stretch::StretchLoop&);
  virtual void operator()(const file::VirtualFile&);
  virtual void operator()(const file::VirtualFileList&);
  virtual void operator()(const gui::LoopPointList&);
  virtual void operator()(const widget::waveform::CursorTime&);
  virtual void operator()(const widget::waveform::TimeAndMouseEvent&);
  virtual void operator()(const widget::waveform::ZoomProto&);
  virtual void operator()(RealTime);
  virtual void operator()(TransportState);

 private:
  Instance* instance_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Listeners);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_LISTENERS__
