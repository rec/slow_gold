#ifndef __REC_WIDGET_WAVEFORM_MOUSEWHEELEVENT__
#define __REC_WIDGET_WAVEFORM_MOUSEWHEELEVENT__

#include "rec/base/base.h"

namespace rec {
namespace widget {
namespace waveform {

struct MouseWheelEvent {
  const MouseEvent* event_;
  float xIncrement_;
  float yIncrement_;

 private:
  JUCE_LEAK_DETECTOR(MouseWheelEvent);
};

}  // namespace waveform
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_WAVEFORM_MOUSEWHEELEVENT__
