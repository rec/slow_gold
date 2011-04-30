#ifndef __REC_GUI_SETTERSLIDER__
#define __REC_GUI_SETTERSLIDER__

#include "rec/data/Value.h"
#include "rec/gui/Layout.h"
#include "rec/gui/SimpleLabel.h"
#include "rec/gui/Geometry.h"
#include "rec/util/listener/ProtoListener.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/util/Range.h"

namespace rec {
namespace gui {

class SetterSlider : public Layout,
                     public ProtoListener,
                     public juce::Slider::Listener {
 public:
  SetterSlider(const String& name,
               const Address& address,
               const String& caption = String::empty,
               const String& tip = String::empty);
  Slider* slider() { return &slider_; }

  virtual void sliderValueChanged(Slider*) { updatePersistentData(); }

 protected:
  virtual const Value getDisplayValue() const { return slider_.getValue(); }
  void setValue(double value) { slider_.setValue(value, false); }
  virtual void setDisplayValue(const Value& value);

  Slider slider_;
  SimpleLabel caption_;

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(SetterSlider);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_SETTERSLIDER__
