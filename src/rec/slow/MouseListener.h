#ifndef __REC_SLOW_MOUSELISTENER__
#define __REC_SLOW_MOUSELISTENER__

#include "rec/base/SampleTime.h"
#include "rec/util/Mode.pb.h"
#include "rec/util/Range.h"
#include "rec/util/Listener.h"
#include "rec/data/DataListener.h"
#include "rec/slow/HasInstance.h"
#include "rec/widget/waveform/Viewport.pb.h"

namespace rec {

namespace util { class Mode; }
namespace widget { namespace waveform { class Cursor; } }
namespace widget { namespace waveform { struct MouseWheelEvent; } }
namespace widget { namespace waveform { class Waveform; } }

namespace slow {

// TODO: rename this to something else to avoid conflicting with Juce's
// MouseListener.
class MouseListener : public HasInstance,
                      public juce::MouseListener,
                      public DataListener<widget::waveform::Viewport>,
                      public GlobalDataListener<Mode>,
                      public Listener<const widget::waveform::MouseWheelEvent&> {
 public:
  MouseListener(Instance* i);
  virtual ~MouseListener() {}

  virtual void mouseDown(const MouseEvent&);
  virtual void mouseDrag(const MouseEvent&);
  virtual void mouseUp(const MouseEvent&);
  virtual void operator()(const widget::waveform::MouseWheelEvent&);
  virtual void setMode(const Mode& m) { mode_ = m; }
  virtual void operator()(const widget::waveform::Viewport&) {}
  virtual void operator()(const Mode& m) { setMode(m); }
  void toggleAddLoopPointMode();

 private:
  void clickWaveform(const MouseEvent&, widget::waveform::Waveform*);
  void dragWaveform(const MouseEvent&, widget::waveform::Waveform*);
  void addLoopPoint(SampleTime);
  void clickCursor(widget::waveform::Cursor*);
  void dragCursor(const MouseEvent&, widget::waveform::Cursor*);

  Mode::Action getClickAction();

  SampleTime waveformDragStart_;
  int cursorDragStart_;
  ModifierKeys dragMods_;
  Range<SampleTime > cursorRestrict_;
  Mode mode_;
  Mode previousMode_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(MouseListener);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_MOUSELISTENER__
