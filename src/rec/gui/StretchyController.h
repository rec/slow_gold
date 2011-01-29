#ifndef __REC_GUI_STRETCHYCONTROLLER__
#define __REC_GUI_STRETCHYCONTROLLER__

#include "rec/gui/SetterSlider.h"
#include "rec/gui/Layout.h"
#include "rec/audio/stretch/Stretchy.pb.h"
#include "rec/gui/SetterToggle.h"

namespace rec {
namespace gui {

class StretchyController : public Layout {
 public:
  StretchyController();
  virtual bool isOpaque() const { return true; }

  void setData(UntypedData* data);
  void enableSliders(bool enabled);

 private:
  SetterSlider playbackSpeed_;
  SetterSlider pitchScale_;
  SetterSlider fineScale_;
  gui::SetterToggle disableButton_;

  DISALLOW_COPY_AND_ASSIGN(StretchyController);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_STRETCHYCONTROLLER__
