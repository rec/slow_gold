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

  SetterSlider(const Address& address, const String& name = String::empty)
      : juce::Slider(name), address_(address), data_(NULL) {
  }

  ~SetterSlider() {
    setData(NULL);
  }

  void setData(Data* data) {
    if (data_)
      data_->removeListener(this);

    data_ = data;

    if (data_) {
      data_->addListener(this);
      (*this)(data_->get());
    }
  }

  virtual void operator()(const Proto& message) {
    proto::Value value = proto::getValue(address_, message);
    if (value.has_double_f())
      (new Updater(this, value.double_f()))->post();
  }

  virtual void valueChanged() {
    if (data_)
      data_->setter()->set(address_, getValue());
  }

 private:
  class Updater : public juce::CallbackMessage {
   public:
    Updater(juce::Slider* s, double v) : slider_(s), value_(v) {}

    virtual void messageCallback() { slider_->setValue(value_, false); }

   private:
    juce::Slider* slider_;
    const double value_;
  };

  const Address address_;
  Data* data_;
  double value_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(SetterSlider);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_SETTERSLIDER__
