#ifndef __REC_GUI_SETTERTOGGLE__
#define __REC_GUI_SETTERTOGGLE__

#include "rec/util/listener/ProtoListener.h"
#include "rec/util/listener/DataListener.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {
namespace gui {

template <typename Proto>
class SetterToggle : public juce::ToggleButton,
                        public DataListener<Proto> {
 public:
  SetterToggle(const String& name, const data::Address& address)
      : juce::ToggleButton(name), DataListener<Proto>(address) {}

  virtual void clicked() {
    setValue(getToggleState());
  }

 protected:
  void setToggle(bool state) {
    setToggleState(state, false);
  }

  virtual void onDataChange(const Proto&) {
    thread::callAsync(this, &SetterToggle<Proto>::setToggle,
    	 								this->getValue().bool_f());
  }

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(SetterToggle);
};


}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_SETTERTOGGLE__
