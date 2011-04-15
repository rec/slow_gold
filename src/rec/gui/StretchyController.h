#ifndef __REC_GUI_STRETCHYCONTROLLER__
#define __REC_GUI_STRETCHYCONTROLLER__

#include "rec/gui/SetterSlider.h"
#include "rec/gui/Layout.h"
#include "rec/audio/stretch/Stretch.pb.h"
#include "rec/gui/SetterToggle.h"

namespace rec {
namespace gui {

class StretchyController : public Layout, public juce::ComboBox::Listener,
                           public DataListener<StretchLoop> {
 public:
  StretchyController();
  virtual bool isOpaque() const { return true; }

  virtual void setData(persist::Data<StretchLoop>* data);

  void setZoom(UntypedData* zoom);
  void enableSliders(bool enabled);
  virtual void comboBoxChanged(juce::ComboBox*);

 private:
  SetterSlider playbackSpeed_;
  SetterSlider pitchScale_;
  SetterSlider fineScale_;
  gui::SetterToggle disableButton_;
  gui::SetterToggle zoomToSelectionButton_;
  gui::SetterToggle clickToZoomButton_;
  juce::ComboBox stereoComboBox_;

  DISALLOW_COPY_AND_ASSIGN(StretchyController);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_STRETCHYCONTROLLER__
