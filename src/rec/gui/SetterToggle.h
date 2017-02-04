#pragma once

#include "rec/app/LanguageListener.h"
#include "rec/data/Address.h"
#include "rec/data/AddressListener.h"
#include "rec/util/Disableable.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {
namespace gui {

class SetterToggle : public app::LanguageListener,
                                          public Disableable,
                                          public data::AddressListener,
                                          public juce::ToggleButton {
  public:
    using Scope = data::AddressProto::Scope;

    SetterToggle(const string& name,
                              const string& tooltip,
                              const data::Address& a)
            : AddressListener(a),
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
