#ifndef __REC_WIDGET_WAVEFORM_TIMEANDMOUSEEVENT__
#define __REC_WIDGET_WAVEFORM_TIMEANDMOUSEEVENT__

#include "rec/base/base.h"

namespace rec {
namespace widget {
namespace waveform {

struct TimeAndMouseEvent {
  double time_;
  const juce::MouseEvent* mouseEvent_;
  int clickCount_;
};

}  // namespace waveform
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_WAVEFORM_TIMEANDMOUSEEVENT__
