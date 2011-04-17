#ifndef __REC_WIDGET_WAVEFORM_CURSOR__
#define __REC_WIDGET_WAVEFORM_CURSOR__

#include <set>

#include "rec/gui/Geometry.h"
#include "rec/util/listener/Listener.h"
#include "rec/widget/Painter.h"
#include "rec/widget/waveform/Cursor.pb.h"
#include "rec/widget/waveform/Waveform.h"

namespace rec {
namespace widget {
namespace waveform {

class Cursor : public Component {
 public:
  Cursor(Instance* instance, const CursorProto& d, Waveform* waveform,
         double time, int index);
  virtual ~Cursor() {}

  void setTime(double time);
  void paint(Graphics& g);
  double getTime() const;

  bool isTimeCursor() const { return this == waveform_->timeCursor(); }

  const CursorProto& desc() const { return desc_; }
  void setCursorBounds(double time);

  virtual void mouseDown(const MouseEvent& e);
  virtual void mouseDrag(const MouseEvent& e);
  virtual void mouseUp(const MouseEvent& e);

 private:
  int getDragX(const MouseEvent& e) const;

  Instance* instance_;
  Waveform* const waveform_;
  CriticalSection lock_;
  CursorProto desc_;
  double time_;
  const int index_;
  juce::Rectangle<int> bounds_;
  bool dragging_;
  int dragX_;
  int mouseDragX_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Cursor);
};

struct CompareCursors {
  bool operator()(Cursor* x, Cursor* y) { return x->getTime() < y->getTime(); }
};

typedef std::set<Cursor*, CompareCursors> CursorSet;

}  // namespace waveform
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_WAVEFORM_CURSOR__
