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

  StretchyController()
      : Layout(VERTICAL, true, "StretchyController"),
        disableButton_("Disable", Address("disable")),
        playbackSpeed_("Playback speed", Address("time_percent")),
        pitchScale_("Transpose", Address("semitone_shift")),
        fineScale_("Fine tuning", Address("detune_cents")) {
    playbackSpeed_.slider()->setRange(0, 200.0, 1.0);
    pitchScale_.slider()->setRange(-7.0, 7.0, 0.5);
    fineScale_.slider()->setRange(-50.0, 50.0, 1.0);

    playbackSpeed_.slider()->setTextValueSuffix("%");
    pitchScale_.slider()->setTextValueSuffix(" semitones");
    fineScale_.slider()->setTextValueSuffix(" cents");

    double portion = -1.0 / 4.0;
    addToLayout(&disableButton_, portion);
    addToLayout(&playbackSpeed_, portion);
    addToLayout(&pitchScale_, portion);
    addToLayout(&fineScale_, portion);
    // getData()->set("disable", disableButton_.getToggleState());
  }

  virtual bool isOpaque() const { return true; }

  void setData(persist::Data<StretchyProto>* data) {
    playbackSpeed_.setData(data);
    pitchScale_.setData(data);
    fineScale_.setData(data);
    disableButton_.setData(data);

    bool enable = !(data && data->get().disabled());
    if (enable != isEnabled())
      thread::callAsync(this, &Component::setEnabled, enable);
  }

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
