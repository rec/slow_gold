#ifndef __REC_GUI_SETTERSLIDER__
#define __REC_GUI_SETTERSLIDER__

#include "rec/gui/Layout.h"
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
      : Layout(Layout::HORIZONTAL, true, name),
        AddressListener<Proto>(address), slider_(name), label_(caption) {
    slider_.setSliderStyle(Slider::LinearHorizontal);
    slider_.setTextBoxStyle(Slider::TextBoxLeft, false, 90, 20);

    const String& cap = caption.length() ? caption : name;
    slider_.setTooltip(tip.length() ? tip : cap);
    slider_.addListener(this);

    label_.setText(cap, false);
    label_.setFont(Font(14.0000f, Font::plain));
    label_.setJustificationType(juce::Justification::centredRight);
    label_.setEditable(false, false, false);
    label_.setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label_.setColour(juce::TextEditor::backgroundColourId, Colour(0x0));

    addToLayout(&label_, 100, -0.3, -0.3);
    addToLayout(&slider_, 100, -0.7, -0.7);
  }

  Slider* slider() { return &slider_; }

  virtual void sliderValueChanged (Slider* slider) { this->onChange(); }

 protected:
  virtual const Value get() const {
    return slider_.getValue();
  }

  virtual void set(const Value& value) {
    if (value.has_double_f())
      thread::callAsync(&slider_, &juce::Slider::setValue, value.double_f(), false);
  }

  Slider slider_;
  juce::Label label_;

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(SetterSlider);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_SETTERSLIDER__
