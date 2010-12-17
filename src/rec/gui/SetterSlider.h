#ifndef __REC_GUI_SETTERSLIDER__
#define __REC_GUI_SETTERSLIDER__

#include "rec/data/proto/Proto.h"
#include "rec/data/persist/Data.h"
#include "rec/util/listener/Listener.h"

namespace rec {
namespace gui {

typedef proto::arg::Address Address;
typedef persist::UntypedData UntypedData;

template <typename Proto>
class SetterSlider : public juce::Slider,
                     public listener::Listener<const Proto&> {
 public:
  typedef proto::arg::Address Address;
  typedef persist::Data<Proto> Data;

  SetterSlider(Data* d, const Address& a,
              const String& name = String::empty)
      : juce::Slider(name), data_(d), address_(a) {
    data_->addListener(this);
  }

  ~SetterSlider() {
    data_->removeListener(this);
  }

  virtual void operator()(const Proto& message) {
    proto::Value value = proto::getValue(address_, message);
    if (value.has_double_f()) {
      juce::MessageManagerLock lock(Thread::getCurrentThread());
      setValue(value.double_f(), false);
    } else {
      LOG(ERROR) << "Got an update but no double value!";
    }
  }

  virtual void valueChanged() {
    data_->setter()->set(address_, getValue());
  }

 private:
  Data* const data_;
  const Address address_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(SetterSlider);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_SETTERSLIDER__
