#ifndef __REC_GUI_DATASLIDER__
#define __REC_GUI_DATASLIDER__

#include "rec/data/Value.h"
#include "rec/gui/DataSlider.h"
#include "rec/gui/DetentSlider.h"
#include "rec/gui/SimpleLabel.h"
#include "rec/gui/layout/Layout.h"
#include "rec/data/DataListener.h"

namespace rec {
namespace gui {

class DataSlider : public Layout,
                   public UntypedDataListener,
                   public juce::Slider::Listener {
 public:
  DataSlider(const String& name,
             const string& typeName,
             const data::Address& address,
             const String& caption = String::empty,
             const String& tip = String::empty)
    : Layout(name, HORIZONTAL, true),
      UntypedDataListener(typeName, address),
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

  void setTooltip(const String& s) {
    slider_.setTooltip(s);
    caption_.setTooltip(s);
    SettableTooltipClient::setTooltip(s);
    slider_.sendLookAndFeelChange();
  }

  virtual void sliderValueChanged(Slider*) {
    this->setValue(static_cast<double>(slider_.getValue()));
  }

  virtual void operator()(const Message&) {
    thread::callAsync(this, &DataSlider::setSliderValue,
                      getValue().get<double>());
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
