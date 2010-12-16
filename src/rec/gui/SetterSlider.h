#ifndef __REC_GUI_SETTERSLIDER__
#define __REC_GUI_SETTERSLIDER__

#include "rec/data/proto/Proto.h"
#include "rec/data/persist/UntypedData.h"
#include "rec/util/listener/Listener.h"

namespace rec {
namespace gui {

class SetterSlider : public juce::Slider,
                     public listener::Listener<UntypedData*> {
 public:
  SetterSlider(UntypedData* d, const Address& a,
                 const String& name = String::empty)
      : juce::Slider(name), data_(d), address_(s) {
    data_->addListener(this);
  }

  ~SetterSlider() {
    data_->removeListener(this);
  }

  virtual void operator()(const Message& message) {
    proto::Value value = getValue(address_, message);
    if (value.has_double())
      setValue(value.double_f(), false);
    else
      LOG(ERROR) << "Got an update but no double value!";
  }

  virtual void valueChanged() {
    data_->setter()->set(address_, getValue());
  }

 private:
  const Address address_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(SetterSlider);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_SETTERSLIDER__
