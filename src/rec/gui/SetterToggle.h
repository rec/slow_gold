#ifndef __REC_GUI_SETTERTOGGLE__
#define __REC_GUI_SETTERTOGGLE__

#include "rec/util/listener/ProtoListener.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {
namespace gui {

class SetterToggle : public juce::ToggleButton,
                     public ProtoListener {
 public:
  SetterToggle(const String& name, const data::Address& address)
      : juce::ToggleButton(name), ProtoListener(address) {}

  virtual void clicked() { updatePersistentData(); }

 protected:
  virtual const data::Value getDisplayValue() const { return getToggleState(); }

  void setToggle(bool state) {
    setToggleState(state, false);
  }

  virtual void setDisplayValue(const data::Value& v) {
    if (v.has_bool_f())
      thread::callAsync(this, &SetterToggle::setToggle, v.bool_f());
  }

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(SetterToggle);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_SETTERTOGGLE__
