#ifndef __REC_GUI_SETTERTOGGLE__
#define __REC_GUI_SETTERTOGGLE__

#include "rec/data/Address.h"
#include "rec/data/AddressListener.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {
namespace gui {

class SetterToggle : public juce::ToggleButton, public data::AddressListener {
 public:
  SetterToggle(const String& name, const string& typeName,
               const data::Address& a, Scope scope = FILE_SCOPE)
      : juce::ToggleButton(name), AddressListener(a, typeName, scope) {
  }

  virtual void clicked() {
    setValue(getToggleState());
  }

 protected:
  void setToggle(bool state) {
    setToggleState(state, false);
  }

  virtual void operator()(const data::Value& v) {
    setToggle(v.bool_f());
  }

 private:
  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(SetterToggle);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_SETTERTOGGLE__
