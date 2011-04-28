#include "rec/gui/SetterSlider.h"

namespace rec {
namespace gui {

SetterSlider::SetterSlider(const String& name, const Address& address,
                           const String& caption, const String& tip)
    : Layout(name, HORIZONTAL, true),
      ProtoListener(address), slider_(name), caption_(caption) {
  slider_.setSliderStyle(Slider::LinearHorizontal);
  slider_.setTextBoxStyle(Slider::TextBoxLeft, false, 85, 16);

  const String& cap = caption.length() ? caption : name;
  slider_.setTooltip(tip.length() ? tip : cap);
  slider_.addListener(this);

  caption_.setText(cap, false);
  addToLayout(&caption_, 100);
  addToLayout(&slider_, 0, -1.0, -1.0);
}

void SetterSlider::setDisplayValue(const Value& value) {
  if (value.has_double_f())
    thread::callAsync(this, &SetterSlider::setValue, value.double_f());
}

}  // namespace gui
}  // namespace rec
