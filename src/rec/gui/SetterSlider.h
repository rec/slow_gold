#ifndef __REC_GUI_SETTERSLIDER__
#define __REC_GUI_SETTERSLIDER__

#include "rec/util/listener/FileDataListener.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {
namespace gui {

template <typename Proto>
class SetterSlider : public juce::Slider,
                     public listener::FileDataListener<Proto> {
 public:
  typedef proto::arg::Address Address;
  typedef proto::arg::Value Value;
  typedef persist::Data<Proto> Data;

  SetterSlider(const String& name, const Address& address, const string& dataFileName)
      : juce::Slider(name),
        listener::FileDataListener<Proto>(address, dataFileName) {
  }

 protected:
  virtual const Value get() const {
    return Slider::getValue();
  }

  virtual void set(const Value& value) {
    if (value.has_double_f())
      callAsync(this, &juce::Slider::setValue, value.double_f(), false);
  }

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(SetterSlider);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_SETTERSLIDER__
