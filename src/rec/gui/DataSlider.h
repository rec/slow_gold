#ifndef __REC_GUI_DATASLIDER__
#define __REC_GUI_DATASLIDER__

#include "rec/data/Value.h"
#include "rec/gui/DetentSlider.h"
#include "rec/gui/layout/Layout.h"
#include "rec/gui/SimpleLabel.h"
#include "rec/util/listener/ProtoListener.h"
#include "rec/util/listener/DataListener.h"

namespace rec {
namespace gui {

template <typename Proto, typename Type>
class DataSlider : public Layout,
                      public DataListener<Proto>,
                      public juce::Slider::Listener {
 public:
  DataSlider(const String& name,
                const data::Address& address,
                const String& caption = String::empty,
                const String& tip = String::empty)
    : Layout(name, HORIZONTAL, true),
      DataListener<Proto>(address),
      slider_(name),
      caption_(caption) {
    slider_.setSliderStyle(Slider::LinearHorizontal);

    // TODO: constants
    slider_.setTextBoxStyle(Slider::TextBoxLeft, false, 70, 12);

    const String& cap = caption.length() ? caption : name;
    slider_.setTooltip(tip.length() ? tip : cap);
    slider_.addListener(this);

    caption_.setText(cap, false);
    // TODO: constants
    addToLayout(&caption_, 45);
    addToLayout(&slider_, 0, -1.0, -1.0);
  }

  DetentSlider* slider() { return &slider_; }

  virtual void sliderValueChanged(Slider*) {
    this->setValue(static_cast<Type>(slider_.getValue()));
  }

  virtual void onDataChange(const Proto&) {
    const data::Value value = this->getValue();
    thread::callAsync(this, &DataSlider<Proto, Type>::setSliderValue,
                      value.get<Type>());
  }

 protected:
  void setSliderValue(Type value) { slider_.setValue(value, false); }

  DetentSlider slider_;
  SimpleLabel caption_;

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(DataSlider);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_DATASLIDER__
