#ifndef __REC_GUI_DATASLIDER__
#define __REC_GUI_DATASLIDER__

#include "rec/app/LanguageListener.h"
#include "rec/data/Address.h"
#include "rec/data/AddressListener.h"
#include "rec/data/DataListener.h"
#include "rec/data/Value.h"
#include "rec/gui/DataSlider.h"
#include "rec/gui/DetentSlider.h"
#include "rec/gui/SimpleLabel.h"
#include "rec/gui/layout/Layout.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {
namespace gui {

class DataSlider : public Layout,
                   public data::AddressListener,
                   public app::LanguageListener,
                   public juce::Slider::Listener {
 public:
  typedef data::AddressProto::Scope Scope;

  DataSlider(const String& name,
             const String& tooltip,
             const string& typeName,
             const data::Address& address,
             Scope scope = data::AddressProto::FILE_SCOPE);

  virtual void sliderValueChanged(Slider*);
  virtual void operator()(const data::Value&);
  virtual void languageChanged();

  DetentSlider* slider() { return &slider_; }

 protected:
  void setSliderValue(double value) {
    slider_.setValue(value, juce::dontSendNotification);
  }

  DetentSlider slider_;
  SimpleLabel caption_;

  String name_;
  String tooltip_;

 private:
  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(DataSlider);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_DATASLIDER__
