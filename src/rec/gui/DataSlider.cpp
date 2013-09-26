#include "rec/gui/DataSlider.h"

namespace rec {
namespace gui {

DataSlider::DataSlider(const String& name,
                       const String& tooltip,
                       const data::Address& address,
                       uint32 captionSize,
                       uint32 textEntryBoxWidth,
                       uint32 textEntryBoxHeight)
    : Panel(name, HORIZONTAL, true),
      data::AddressListener(address),
      slider_(name + ".slider"),
      caption_(name + ".caption"),
      name_(name),
      tooltip_(tooltip) {
  slider_.setSliderStyle(Slider::LinearHorizontal);
  slider_.setTextBoxStyle(Slider::TextBoxLeft, false,
                          textEntryBoxWidth, textEntryBoxHeight);
  slider_.addListener(this);

  addToPanel(&caption_, captionSize);
  addToPanel(&slider_, 0, -1.0, -1.0);
}

void DataSlider::sliderValueChanged(Slider*) {
  setValue(slider_.getValue());
}

void DataSlider::operator()(const data::Value& v) {
  setSliderValue(v.double_f());
}

void DataSlider::languageChanged() {
  String s = Trans(str(name_));
  caption_.setText(s, juce::sendNotification);

  String t = Trans(str(tooltip_));
  slider_.setTooltip(t);
  caption_.setTooltip(t);
  SettableTooltipClient::setTooltip(t);

  slider_.sendLookAndFeelChange();
}

}  // namespace gui
}  // namespace rec

