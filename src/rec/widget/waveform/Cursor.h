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

class Cursor : public Component, public listener::Listener<double> {
 public:
  Cursor(const CursorProto& d, Waveform* waveform, double time);
  virtual ~Cursor() {}

  virtual void operator()(double t) { setTime(t); }

  void setTime(double time);
  void paint(Graphics& g);
  double getTime() const;

  const CursorProto& desc() const { return desc_; }

 private:
  Waveform* const waveform_;
  CriticalSection lock_;
  const CursorProto desc_;
  double time_;
  juce::Rectangle<int> bounds_;

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
