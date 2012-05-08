#ifndef __REC_GUI_SETTERLABEL__
#define __REC_GUI_SETTERLABEL__

#include "rec/data/Value.h"
#include "rec/gui/SimpleLabel.h"
#include "rec/data/AddressListener.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {
namespace gui {

class SetterLabel : public SimpleLabel, public data::AddressListener {
 public:
  SetterLabel(const String& name,
              const string& typeName,
              const data::Address& address)
      : SimpleLabel(name), data::AddressListener(address, typeName) {
  }

  void operator()(const data::Value& v) {
    if (v.has_string_f()) {
      String s = str(v.string_f());
      if (s != getText(true))
        setText(s, false);
    }
  }

  void textEditorTextChanged(TextEditor&) {
    setValue(str(getText(true)));
  }

  void setEditorBackground(const juce::Colour& c) {
    setColour(juce::Label::backgroundColourId, c);
  }

 private:
  DISALLOW_COPY_ASSIGN_AND_LEAKS(SetterLabel);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_SETTERLABEL__
