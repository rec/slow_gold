#ifndef __REC_GUI_SETTERTOGGLE__
#define __REC_GUI_SETTERTOGGLE__

#include "rec/util/listener/AddressListener.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {
namespace gui {

template <typename Proto>
class SetterToggle : public juce::ToggleButton,
                     public AddressListener<Proto> {
 public:
  typedef proto::arg::Address Address;
  typedef proto::arg::Value Value;
  typedef persist::Data<Proto> Data;

  SetterToggle(const String& name, const Address& address)
      : juce::ToggleButton(name), AddressListener<Proto>(address) {}

  virtual void clicked() {
    this->onChange();
  }

 protected:
  virtual const Value get() const {
    DLOG(INFO) << "toggleState " << getToggleState();
    return getToggleState();
  }

  virtual void set(const Value& v) {
    if (v.has_bool_f())
      thread::callAsync(this, &juce::Button::setToggleState, v.bool_f(), false);
  }

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(SetterToggle);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_SETTERTOGGLE__
