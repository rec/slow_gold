#ifndef __REC_GUI_STRETCHYCONTROLLER__
#define __REC_GUI_STRETCHYCONTROLLER__

#include "rec/gui/SetterSlider.h"
#include "rec/gui/Layout.h"
#include "rec/audio/source/Stretchy.pb.h"
#include "rec/gui/SetterToggle.h"

namespace rec {
namespace gui {

class StretchyController : public Layout {
 public:
  typedef audio::source::StretchyProto StretchyProto;
 	typedef SetterSlider<StretchyProto> StretchySlider;
  typedef proto::arg::Address Address;

  StretchyController();
  virtual bool isOpaque() const { return true; }

  void setData(persist::Data<StretchyProto>* data);
  void enableSliders(bool enabled);

 private:
  gui::SetterToggle<StretchyProto> disableButton_;
  StretchySlider playbackSpeed_;
  StretchySlider pitchScale_;
  StretchySlider fineScale_;

  DISALLOW_COPY_AND_ASSIGN(StretchyController);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_STRETCHYCONTROLLER__
