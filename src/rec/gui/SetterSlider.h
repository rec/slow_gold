#ifndef __REC_GUI_SETTERSLIDER__
#define __REC_GUI_SETTERSLIDER__

#include "rec/data/Value.h"
#include "rec/gui/DetentSlider.h"
#include "rec/gui/Layout.h"
#include "rec/gui/SimpleLabel.h"
#include "rec/gui/Geometry.h"
#include "rec/util/listener/ProtoListener.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/util/Range.h"

namespace rec {
namespace gui {

template <typename Type>
class DataSlider : public Layout,
                   public ProtoListener,
                   public juce::Slider::Listener {
 public:
  DataSlider(const String& name, const Address& address,
             const String& caption = String::empty,
             const String& tip = String::empty)
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

  DetentSlider* slider() { return &slider_; }

  virtual void sliderValueChanged(Slider*) { updatePersistentData(); }

 protected:
  virtual const Value getDisplayValue() const { return slider_.getValue(); }
  void setValue(Type value) { slider_.setValue(value, false); }
  virtual void setDisplayValue(const Value& value);

  DetentSlider slider_;
  SimpleLabel caption_;

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(DataSlider);
};


template <>
inline void DataSlider<double>::setDisplayValue(const Value& value) {
  if (value.has_double_f())
    thread::callAsync(this, &DataSlider<double>::setValue, value.double_f());
}

template <>
inline void DataSlider<float>::setDisplayValue(const Value& value) {
  if (value.has_float_f())
    thread::callAsync(this, &DataSlider<float>::setValue, value.float_f());
}

typedef DataSlider<double> SetterSlider;

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_SETTERSLIDER__
