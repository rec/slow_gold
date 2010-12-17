#ifndef __REC_WIDGET_WAVEFORM_CURSOR__
#define __REC_WIDGET_WAVEFORM_CURSOR__

#include "rec/gui/Geometry.h"
#include "rec/util/listener/Time.h"
#include "rec/widget/Painter.h"
#include "rec/widget/waveform/Cursor.pb.h"
#include "rec/widget/waveform/Waveform.h"

namespace rec {
namespace widget {
namespace waveform {

class Cursor : public Component, public listener::Time {
 public:
  Cursor(const CursorProto& d, Waveform* waveform, float time = 0f)
      : Component("Cursor"), desc_(d), waveform_(waveform) {
    waveform->addChildComponent(this);
    setTime(time);
  }

  static const float SAMPLE_RATE = 44100f;
  virtual void operator()(float t) { setTime(t); }

  void setTime(float time) {
    ScopedLock l(lock_);
    time_ = time;
    waveform_->layoutCursor(this);
  }

  void paint(Graphics& g) {
    ScopedLock l(lock_);
    Painter p(desc_.widget(), &g);
    juce::Rectangle<int> bounds = getLocalBounds();

    float middle = bounds.getWidth() / 2.0F;
    float margin = desc_.widget().margin();
    float bottom = bounds.getHeight() - 2.0F * margin;

    gui::drawLine(g, desc_.line(), middle, margin, middle, bottom);
  }

  float getTime() const {
    ScopedLock l(lock_);
    return time_;
  }

  const CursorProto& desc() const { return desc_; }

 private:
  CriticalSection lock_;
  const CursorProto desc_;
  float time_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Cursor);
};

}  // namespace waveform
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_WAVEFORM_CURSOR__
