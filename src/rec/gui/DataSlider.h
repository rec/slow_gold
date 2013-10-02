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
#include "rec/gui/proto/Panel.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {
namespace gui {

class DataSlider : public Panel,
                   public data::AddressListener,
                   public app::LanguageListener,
                   public juce::Slider::Listener {
 public:
  DataSlider(const String& name,
             const String& tooltip,
             const String& caption,
             const data::Address& address,
             uint32 captionSize = 45,
             uint32 textEntryBoxWidth = 80,
             uint32 textEntryBoxHeight = 1);
  virtual void sliderValueChanged(Slider*);
  virtual void operator()(const data::Value&);
  virtual void languageChanged();

  DetentSlider* slider() { return slider_; }
  void setDetent(double detent) { slider_->setDetent(detent); }
  void setDetentRadius(double radius) { slider_->setDetentRadius(radius); }
  void setRange(double min, double max, double interval) {
    slider_->setRange(min, max, interval);
  }

 protected:
  void setSliderValue(double value) {
    slider_->setValue(value, juce::dontSendNotification);
  }

  DetentSlider* slider_;
  SimpleLabel* caption_;

  String name_;
  String captionText_;
  String tooltip_;

 private:
  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(DataSlider);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_DATASLIDER__
