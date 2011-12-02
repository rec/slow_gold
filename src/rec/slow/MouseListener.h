#ifndef __REC_SLOW_MOUSELISTENER__
#define __REC_SLOW_MOUSELISTENER__

#include "rec/base/Samples.h"
#include "rec/util/Mode.pb.h"
#include "rec/util/Range.h"
#include "rec/util/Listener.h"
#include "rec/util/DataListener.h"
#include "rec/widget/waveform/Zoom.pb.h"
#include "rec/slow/HasInstance.h"

namespace rec {

namespace util { class Mode; }
namespace widget { namespace waveform { struct MouseWheelEvent; }}

namespace slow {

class MouseListener : public HasInstance,
                      public juce::MouseListener,
                      public DataListener<widget::waveform::ZoomProto>,
                      public DataListener<Mode>,
                      public Listener<const widget::waveform::MouseWheelEvent&> {
 public:
  MouseListener(Instance* i);

  virtual void mouseDown(const MouseEvent&);
  virtual void mouseDrag(const MouseEvent&);
  virtual void mouseUp(const MouseEvent&);
  virtual void operator()(const widget::waveform::MouseWheelEvent&);
  virtual void setMode(const Mode& m) { mode_ = m; }
  virtual void onDataChange(const widget::waveform::ZoomProto&) {}
  virtual void onDataChange(const Mode& m) { setMode(m); }
  void toggleAddLoopPointMode();

 private:
  Mode::Action getClickAction();

  Samples<44100> waveformDragStart_;
  ModifierKeys dragMods_;
  Range<Samples<44100> > cursorDrag_;
  Mode mode_;
  Mode previousMode_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(MouseListener);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_MOUSELISTENER__
