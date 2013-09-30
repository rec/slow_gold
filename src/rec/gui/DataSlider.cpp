#include "rec/gui/DataSlider.h"

namespace rec {
namespace gui {

DataSlider::DataSlider(const String& name,
                       const String& tooltip,
                       const String& caption,
                       const data::Address& address,
                       uint32 captionSize,
                       uint32 textEntryBoxWidth,
                       uint32 textEntryBoxHeight)
    : Panel(name),
      data::AddressListener(address),
      slider_(new DetentSlider(name + ".slider")),
      caption_(new SimpleLabel(caption, name + ".caption")),
      name_(name),
      captionText_(caption),
      tooltip_(tooltip) {
  slider_->setSliderStyle(Slider::LinearHorizontal);
  slider_->setTextBoxStyle(Slider::TextBoxLeft, false,
                          textEntryBoxWidth, textEntryBoxHeight);
  slider_->addListener(this);

  addToPanel(caption_, captionSize);
  addToPanel(slider_, 0, -1.0, -1.0);
}

void DataSlider::sliderValueChanged(Slider*) {
  setValue(slider_->getValue());
}

void DataSlider::operator()(const data::Value& v) {
  setSliderValue(v.double_f());
}

void DataSlider::languageChanged() {
  String s = captionText_;
  if (s.length())
    s = Trans(str(captionText_));

  caption_->setText(s, juce::sendNotification);

  String t = Trans(str(tooltip_));
  slider_->setTooltip(t);
  caption_->setTooltip(t);
  SettableTooltipClient::setTooltip(t);

  slider_->sendLookAndFeelChange();
}

}  // namespace gui
}  // namespace rec
