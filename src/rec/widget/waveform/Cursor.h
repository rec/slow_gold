#ifndef __REC_WIDGET_WAVEFORM_CURSOR__
#define __REC_WIDGET_WAVEFORM_CURSOR__

#include "rec/widget/Painter.h"
#include "rec/gui/Geometry.h"
#include "rec/widget/waveform/Cursor.pb.h"
#include "rec/widget/waveform/Waveform.h"

namespace rec {
namespace widget {
namespace waveform {

class Cursor : public Component {
 public:
  Cursor(const CursorProto& d) : Component("Cursor"), desc_(d), time_(0.0f) {}

  float getTime() const { return time_; }
  void setTime(int time) { time_ = time; }
  const CursorProto& desc() const { return desc_; }

  void paint(Graphics& g) {
    Painter p(desc_.widget(), &g);
    juce::Rectangle<int> bounds = getLocalBounds();

    float middle = bounds.getWidth() / 2.0F;
    float margin = desc_.widget().margin();
    float bottom = bounds.getHeight() - 2.0F * margin;

    gui::drawLine(g, desc_.line(), middle, margin, middle, bottom);
  }

 private:
  CursorProto desc_;
  float time_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Cursor);
};

}  // namespace waveform
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_WAVEFORM_CURSOR__
