#pragma once

#include "rec/base/SampleTime.h"
#include "rec/util/Mode.pb.h"
#include "rec/util/range/Range.h"
#include "rec/util/Listener.h"
#include "rec/data/DataListener.h"
#include "rec/widget/waveform/Viewport.pb.h"

namespace rec {

namespace util { class Mode; }
namespace widget { namespace waveform { class Cursor; } }
namespace widget { namespace waveform { struct MouseWheelEvent; } }
namespace widget { namespace waveform { class Waveform; } }

namespace slow {

class MouseListener : public juce::MouseListener,
                      public DataListener<widget::waveform::Viewport>,
                      public DataListener<Mode>,
                      public Listener<const widget::waveform::MouseWheelEvent&> {
 public:
  MouseListener();
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
  bool groupingUndoEvents_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(MouseListener);
};

}  // namespace slow
}  // namespace rec

