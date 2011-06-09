#ifndef __REC_WIDGET_WAVEFORM_CURSOR__
#define __REC_WIDGET_WAVEFORM_CURSOR__

#include <set>

#include "rec/audio/Audio.h"
#include "rec/gui/Geometry.h"
#include "rec/util/listener/Listener.h"
#include "rec/widget/Painter.h"
#include "rec/widget/waveform/Cursor.pb.h"
#include "rec/widget/waveform/Waveform.h"

namespace rec {
namespace widget {
namespace waveform {

class Cursor : public Component, public Listener<SamplePosition> {
 public:
  Cursor(const CursorProto& d, Waveform* waveform, RealTime time, int index);
  virtual ~Cursor() {}

  void setTime(RealTime time);
  void setTime(SamplePosition time);
  void paint(Graphics& g);
  double getTime() const;

  bool isTimeCursor() const { return this == waveform_->timeCursor(); }

  const CursorProto& desc() const { return desc_; }
  void setCursorBounds(double time);

  virtual void operator()(SamplePosition t);

  void setListeningToClock(bool b) { listeningToClock_ = b; }
  int index() { return index_; }

 private:
  Waveform* const waveform_;
  CriticalSection lock_;
  CursorProto desc_;
  RealTime time_;
  const int index_;
  juce::Rectangle<int> bounds_;
  bool dragging_;
  int dragX_;
  int mouseDragX_;
  bool listeningToClock_;

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
