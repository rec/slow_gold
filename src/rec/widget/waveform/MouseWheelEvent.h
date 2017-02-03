#pragma once

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

