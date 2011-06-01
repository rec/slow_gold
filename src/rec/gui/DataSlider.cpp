#include "rec/gui/DataSlider.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/util/Range.h"
// #include "rec/gui/Geometry.h"

namespace rec {
namespace gui {

template <typename Type>
DataSlider<Type>::DataSlider(const String& name, const Address& address,
                             const String& caption,
                             const String& tip)
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

template <typename Type>
void DataSlider<Type>::setDisplayValue(const Value& value) {
  if (value.has<Type>())
    thread::callAsync(this, &DataSlider<Type>::setValue, value.get<Type>());
}

template class DataSlider<float>;
template class DataSlider<double>;
template class DataSlider<int32>;

}  // namespace gui
}  // namespace rec
