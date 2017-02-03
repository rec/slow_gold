#pragma once

#include "rec/base/base.h"

namespace rec {
namespace gui {

class DetentSlider : public juce::Slider {
 public:
  explicit DetentSlider(const String& name = String::empty) :
      Slider(name), detentRadius_(0.05f), detentSet_(false) {
    setTextBoxIsEditable(true);
  }

  void setDetent(float d) { detent_ = d; detentSet_ = true; }
  void setDetentRadius(float r) { detentRadius_ = r; }
  void clearDetent() { detentSet_ = false; }

  double snapValue(double value, juce::Slider::DragMode dragMode) override {
    if (dragMode == juce::Slider::notDragging or not detentSet_)
      return value;

    float d = fabsf(getPositionOfValue(value) - getPositionOfValue(detent_));
    float width = static_cast<float>(getMaximum() - getMinimum());
    return (d < (detentRadius_ * width)) ? detent_ : value;
  }

  void resetToDetent() {
    if (detentSet_)
      setValue(detent_);
  }

 private:
  double detent_;
  float detentRadius_;
  bool detentSet_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(DetentSlider);
};

}  // namespace gui
}  // namespace rec

