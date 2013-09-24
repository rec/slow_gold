#ifndef __REC_GUI_SIMPLELABEL__
#define __REC_GUI_SIMPLELABEL__

#include "rec/base/base.h"

namespace rec {
namespace gui {

class SimpleLabel : public juce::Label {
 public:
  SimpleLabel(const String& name = String::empty,
              const String& labelText = String::empty)
      : juce::Label(name, labelText.length() ? labelText : name) {
    setFont(Font(12.0000f, Font::bold));
    setJustificationType(Justification::centredRight);
    setEditable(false, false, false);
    setColour(juce::TextEditor::textColourId, juce::Colours::black);
    setColour(juce::TextEditor::backgroundColourId, Colour(0x0));
  }

  void setTextIfChanged(const String& newText, juce::NotificationType t) {
    if (newText != getText(true))
        setText(newText, t);
  }

 private:
  DISALLOW_COPY_ASSIGN_AND_LEAKS(SimpleLabel);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_SIMPLELABEL__
