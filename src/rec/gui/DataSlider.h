#ifndef __REC_GUI_DATASLIDER__
#define __REC_GUI_DATASLIDER__

#include "rec/data/Value.h"
#include "rec/gui/DetentSlider.h"
#include "rec/gui/layout/Layout.h"
#include "rec/gui/SimpleLabel.h"
#include "rec/util/listener/ProtoListener.h"

namespace rec {
namespace gui {

template <typename Type>
class DataSlider : public Layout,
                   public ProtoListener,
                   public juce::Slider::Listener {
 public:
  DataSlider(const String& name, 
             const data::Address& address,
             const String& caption = String::empty,
             const String& tip = String::empty);

  DetentSlider* slider() { return &slider_; }

  virtual void sliderValueChanged(Slider*) { updatePersistentData(); }

 protected:
  virtual const data::Value getDisplayValue() const { return slider_.getValue(); }
  void setValue(Type value) { slider_.setValue(value, false); }
  virtual void setDisplayValue(const data::Value& value);

  DetentSlider slider_;
  SimpleLabel caption_;

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(DataSlider);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_DATASLIDER__
