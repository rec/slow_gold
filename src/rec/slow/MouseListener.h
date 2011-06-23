#ifndef __REC_SLOW_MOUSELISTENER__
#define __REC_SLOW_MOUSELISTENER__

#include "rec/base/RealTime.h"
#include "rec/util/Mode.pb.h"
#include "rec/util/Range.h"
#include "rec/util/listener/Listener.h"
#include "rec/slow/HasInstance.h"

namespace rec {

namespace util { class Mode; }
namespace widget { namespace waveform { class MouseWheelEvent; }}

namespace slow {

class MouseListener : public juce::MouseListener, public HasInstance,
                      public Listener<const widget::waveform::MouseWheelEvent&> {
 public:
  MouseListener(Instance* i);

  virtual void mouseDoubleClick(const MouseEvent&);
  virtual void mouseDown(const MouseEvent&);
  virtual void mouseDrag(const MouseEvent&);
  virtual void mouseUp(const MouseEvent&);
  virtual void operator()(const widget::waveform::MouseWheelEvent&);
  virtual void setMode(const Mode& m) { mode_ = m; }

 private:
  Mode::Action getClickAction(const MouseEvent&);

  RealTime waveformDragStart_;
  Range<RealTime> cursorDrag_;
  Mode mode_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(MouseListener);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_MOUSELISTENER__
