#ifndef __REC_GUI_SETTERTOGGLE__
#define __REC_GUI_SETTERTOGGLE__

#include "rec/util/listener/UntypedAddressListener.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {
namespace gui {

class SetterToggle : public juce::ToggleButton,
                     public UntypedAddressListener {
 public:
  SetterToggle(const String& name, const Address& address)
      : juce::ToggleButton(name), UntypedAddressListener(address) {}

  virtual void clicked() {
    this->updatePersistentData();
  }

 protected:
  virtual const Value get() const { return getToggleState(); }

  void setToggle(bool state) {
    setToggleState(state, false);
  }

  virtual void set(const Value& v) {
    if (v.has_bool_f())
      thread::callAsync(this, &SetterToggle::setToggle, v.bool_f());
  }

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(SetterToggle);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_SETTERTOGGLE__
