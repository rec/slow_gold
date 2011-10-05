#ifndef __REC_GUI_DETENTSLIDER__
#define __REC_GUI_DETENTSLIDER__

#include "rec/base/base.h"

namespace rec {
namespace gui {

class DetentSlider : public juce::Slider {
 public:
  explicit DetentSlider(const String& name = String::empty) :
      Slider(name), detentRadius_(1.0f), detentSet_(false) {
  }

  void setDetent(float d) { detent_ = d; detentSet_ = true; }
  void setDetentRadius(float r) { detentRadius_ = r; }
  void clearDetent() { detentSet_ = false; }

  virtual double snapValue(double value, bool userIsDragging) {
    if (!(userIsDragging && detentSet_))
      return value;

    float d = fabsf(getPositionOfValue(value) - getPositionOfValue(detent_));
    return (d < detentRadius_) ? detent_ : value;
  }

  void resetToDetent() {
    if (detentSet_)
      setValue(detent_);
  }

 private:
  double detent_;
  float detentRadius_;
  bool detentSet_;

  DISALLOW_COPY_AND_ASSIGN(DetentSlider);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_DETENTSLIDER__
