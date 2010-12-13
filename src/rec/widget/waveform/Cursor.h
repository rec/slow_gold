#ifndef __REC_WIDGET_WAVEFORM_CURSOR__
#define __REC_WIDGET_WAVEFORM_CURSOR__

#include "rec/widget/Painter.h"

namespace rec {
namespace widget {
namespace waveform {

class Cursor : public Component {
 public:
  Cursor(const CursorProto& desc) : desc_(desc) {}

  void Cursor::paint(Graphics& g) {
    Painter p(desc_.widget(), &g);
    Rectangle<int> bounds = getLocalBounds();

    float middle = bounds.getWidth() / 2.0F;
    float margin = desc_.widget().margin();
    float bottom = bounds.getHeight() - 2.0F * margin;

    drawLine(g, desc_.line(), middle, margin, middle, bottom);
  }

 private:
  CursorProto desc_;
  DISALLOW_COPY_ASSIGN_AND_EMPTY(Cursor);
};

}  // namespace waveform
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_WAVEFORM_CURSOR__
