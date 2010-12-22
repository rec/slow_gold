#ifndef __REC_GUI_SETTERSLIDER__
#define __REC_GUI_SETTERSLIDER__

#include "rec/util/listener/FileDataListener.h"

namespace rec {
namespace gui {

template <typename Proto>
class SetterSlider : public juce::Slider,
                     public listener::FileDataListener<Proto> {
 public:
  typedef proto::arg::Address Address;
  typedef proto::arg::Value Value;
  typedef persist::Data<Proto> Data;

  SetterSlider(const string& dataFileName, const Address& address, const String& name)
      : juce::Slider(name),
        listener::FileDataListener<Proto>(address, dataFileName) {
  }

 protected:
  virtual const Value get() const {
    return Slider::getValue();
  }

  virtual void set(const Value& value) {
    if (value.has_double_f())
      (new Updater(this, value.double_f()))->post();
  }

 private:
  class Updater : public juce::CallbackMessage {
   public:
    Updater(juce::Slider* s, double v) : slider_(s), value_(v) {}

    virtual void messageCallback() { slider_->setValue(value_, false); }

   private:
    juce::Slider* const slider_;
    const double value_;
  };

  DISALLOW_COPY_ASSIGN_AND_EMPTY(SetterSlider);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_SETTERSLIDER__
