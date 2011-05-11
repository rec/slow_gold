#ifndef __REC_SLOW_MOUSELISTENER__
#define __REC_SLOW_MOUSELISTENER__

#include "rec/util/listener/Listener.h"
#include "rec/slow/HasInstance.h"

namespace rec {

namespace widget { namespace waveform { class MouseWheelEvent; }}

namespace slow {

class MouseListener : public juce::MouseListener, public HasInstance,
                      public Listener<const widget::waveform::MouseWheelEvent&> {
 public:
  MouseListener(Instance* i);

  virtual void mouseDoubleClick(const MouseEvent& e);
  virtual void mouseDown(const MouseEvent& e);
  virtual void mouseDrag(const MouseEvent& e);
  virtual void mouseUp(const MouseEvent& e);
  virtual void operator()(const widget::waveform::MouseWheelEvent& e);

 private:
  RealTime waveformDragStart_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(MouseListener);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_MOUSELISTENER__
