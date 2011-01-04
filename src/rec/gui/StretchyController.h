#ifndef __REC_GUI_STRETCHYCONTROLLER__
#define __REC_GUI_STRETCHYCONTROLLER__

#include "rec/gui/SetterSlider.h"
#include "rec/gui/Layout.h"
#include "rec/audio/source/Stretchy.pb.h"

namespace rec {
namespace gui {

class StretchyController : public Layout {
 public:
  typedef audio::source::StretchyProto StretchyProto;
 	typedef SetterSlider<StretchyProto> StretchySlider;
  typedef proto::arg::Address Address;

  StretchyController()
      : Layout(Layout::VERTICAL, true, "StretchyController"),
        playbackSpeed_("Playback speed", Address("time_percent")),
        pitchScale_("Transpose", Address("semitone_shift")),
        fineScale_("Fine tuning", Address("detune_cents")) {
    playbackSpeed_.slider()->setRange(0, 200.0, 1.0);
    pitchScale_.slider()->setRange(-7.0, 7.0, 0.5);
    fineScale_.slider()->setRange(-50.0, 50.0, 1.0);

    playbackSpeed_.slider()->setTextValueSuffix("%");
    pitchScale_.slider()->setTextValueSuffix(" semitones");
    fineScale_.slider()->setTextValueSuffix(" cents");

    addToLayout(&playbackSpeed_, -1.0/3.0);
    addToLayout(&pitchScale_, -1.0/3.0);
    addToLayout(&fineScale_, -1.0/3.0);
  }

  virtual bool isOpaque() const { return true; }

  void setData(persist::Data<StretchyProto>* data) {
    playbackSpeed_.setData(data);
    pitchScale_.setData(data);
    fineScale_.setData(data);
  }

 private:
  StretchySlider playbackSpeed_;
  StretchySlider pitchScale_;
  StretchySlider fineScale_;

  DISALLOW_COPY_AND_ASSIGN(StretchyController);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_STRETCHYCONTROLLER__
