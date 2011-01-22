#ifndef __REC_GUI_SETTERSLIDER__
#define __REC_GUI_SETTERSLIDER__

#include "rec/gui/Layout.h"
#include "rec/gui/SimpleLabel.h"
#include "rec/gui/Geometry.h"
#include "rec/util/listener/AddressListener.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/util/Range.h"

namespace rec {
namespace gui {

template <typename Proto>
class SetterSlider : public Layout,
                     public AddressListener<Proto>,
                     public juce::Slider::Listener {
 public:
  typedef proto::arg::Address Address;
  typedef proto::arg::Value Value;
  typedef persist::Data<Proto> Data;

  SetterSlider(const String& name, const Address& address,
               const String& caption = String::empty,
               const String& tip = String::empty)
      : Layout(name, HORIZONTAL, true),
        AddressListener<Proto>(address), slider_(name), caption_(caption) {
    slider_.setSliderStyle(Slider::LinearHorizontal);
    slider_.setTextBoxStyle(Slider::TextBoxLeft, false, 85, 16);

    const String& cap = caption.length() ? caption : name;
    slider_.setTooltip(tip.length() ? tip : cap);
    slider_.addListener(this);

    caption_.setText(cap, false);
    addToLayout(&caption_, 100);
    addToLayout(&slider_, 0, -1.0, -1.0);
  }

  Slider* slider() { return &slider_; }

  virtual void sliderValueChanged (Slider* slider) { 
    this->updatePersistentData(); 
  }

 protected:
  virtual const Value get() const {
    return slider_.getValue();
  }

  void setValue(double value) {
    slider_.setValue(value, false);
  }

  virtual void set(const Value& value) {
    if (value.has_double_f())
      thread::callAsync(this, &SetterSlider::setValue, value.double_f());
  }

  Slider slider_;
  SimpleLabel caption_;

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(SetterSlider);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_SETTERSLIDER__
