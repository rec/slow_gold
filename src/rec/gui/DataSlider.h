#ifndef __REC_GUI_DATASLIDER__
#define __REC_GUI_DATASLIDER__

#include "rec/data/Address.h"
#include "rec/data/AddressListener.h"
#include "rec/data/DataListener.h"
#include "rec/data/Value.h"
#include "rec/gui/DataSlider.h"
#include "rec/gui/DetentSlider.h"
#include "rec/gui/SimpleLabel.h"
#include "rec/gui/layout/Layout.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {
namespace gui {

class DataSlider : public Layout,
                   public data::AddressListener,
                   public juce::Slider::Listener {
 public:
  DataSlider(const String& name,
             const string& typeName,
             const data::Address& address,
             const String& caption = String::empty,
             const String& tip = String::empty,
             Scope scope = FILE_SCOPE)
    : Layout(name, HORIZONTAL, true),
      data::AddressListener(address, typeName, scope),
      slider_(name),
      caption_(caption) {
    slider_.setSliderStyle(Slider::LinearHorizontal);

    // TODO: constants
    slider_.setTextBoxStyle(Slider::TextBoxLeft, false, 80, 16);

    const String& cap = caption.length() ? caption : name;
    slider_.setTooltip(tip.length() ? tip : cap);
    slider_.addListener(this);

    caption_.setText(cap, false);
    // TODO: constants
    addToLayout(&caption_, 45);
    addToLayout(&slider_, 0, -1.0, -1.0);
  }

  void setTooltip(const String& s) {
    slider_.setTooltip(s);
    caption_.setTooltip(s);
    SettableTooltipClient::setTooltip(s);
    slider_.sendLookAndFeelChange();
  }

  virtual void sliderValueChanged(Slider*) {
    setValue(slider_.getValue());
  }

  virtual void operator()(const data::Value& v) {
    setSliderValue(v.double_f());
  }

  DetentSlider* slider() { return &slider_; }

 protected:
  void setSliderValue(double value) { slider_.setValue(value, false); }

  DetentSlider slider_;
  SimpleLabel caption_;

 private:
  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(DataSlider);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_DATASLIDER__
