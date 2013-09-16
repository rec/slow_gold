#ifndef __REC_GUI_SETTERTOGGLE__
#define __REC_GUI_SETTERTOGGLE__

#include "rec/app/LanguageListener.h"
#include "rec/data/Address.h"
#include "rec/data/AddressListener.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {
namespace gui {

class SetterToggle : public app::LanguageListener,
                     public data::AddressListener,
                     public juce::ToggleButton {
 public:
  typedef data::AddressProto::Scope Scope;

  SetterToggle(const string& name,
               const string& tooltip,
               const string& typeName,
               const data::Address& a)
      : AddressListener(a, typeName),
        juce::ToggleButton(str(name)),
        name_(name),
        tooltip_(tooltip) {
  }

  virtual void clicked() {
    setValue(getToggleState());
  }

  virtual void languageChanged() {
    setName(Trans(name_));
    setTooltip(Trans(tooltip_));
  }

 protected:
  void setToggle(bool state) {
    setToggleState(state, juce::dontSendNotification);
  }

  virtual void operator()(const data::Value& v) {
    setToggle(v.bool_f());
  }

 private:
  string name_;
  string tooltip_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(SetterToggle);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_SETTERTOGGLE__
