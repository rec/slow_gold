#ifndef __REC_GUI_SETTERTOGGLE__
#define __REC_GUI_SETTERTOGGLE__

#include "rec/data/UntypedDataListener.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {
namespace gui {

class SetterToggle : public juce::ToggleButton,
                     public UntypedDataListener {
 public:
  SetterToggle(const String& name, const string& typeName,
               const data::Address& address)
      : juce::ToggleButton(name), UntypedDataListener(typeName, address) {
  }

  virtual void clicked() {
    this->setValue(getToggleState());
  }

 protected:
  void setToggle(bool state) {
    setToggleState(state, false);
  }

  virtual void operator()(const Message&) {
    thread::callAsync(this, &SetterToggle::setToggle, getValue().bool_f());
  }

 private:
  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(SetterToggle);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_SETTERTOGGLE__
