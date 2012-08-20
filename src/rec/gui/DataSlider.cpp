#include "rec/gui/DataSlider.h"

namespace rec {
namespace gui {

DataSlider::DataSlider(const String& name,
                       const String& tooltip,
                       const string& typeName,
                       const data::Address& address,
                       Scope scope)
    : Layout(name, HORIZONTAL, true),
      data::AddressListener(address, typeName, scope),
      slider_(name),
      caption_(name),
      name_(name),
      tooltip_(tooltip) {
  slider_.setSliderStyle(Slider::LinearHorizontal);

  // TODO: constants
  slider_.setTextBoxStyle(Slider::TextBoxLeft, false, 80, 16);

  slider_.addListener(this);

  // TODO: constants
  addToLayout(&caption_, 45);
  addToLayout(&slider_, 0, -1.0, -1.0);
}

void DataSlider::sliderValueChanged(Slider*) {
  setValue(slider_.getValue());
}

void DataSlider::operator()(const data::Value& v) {
  setSliderValue(v.double_f());
}

void DataSlider::languageChanged() {
  String s = Trans(str(name_));
  caption_.setText(s, true);

  String t = Trans(str(tooltip_));
  slider_.setTooltip(t);
  caption_.setTooltip(t);
  SettableTooltipClient::setTooltip(t);

  slider_.sendLookAndFeelChange();
}

}  // namespace gui
}  // namespace rec

