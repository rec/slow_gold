#ifndef __REC_GUI_AUDIO_GAINCONTROLLER__
#define __REC_GUI_AUDIO_GAINCONTROLLER__

#include "rec/gui/SetterSlider.h"
#include "rec/gui/Layout.h"
#include "rec/audio/util/Gain.h"
#include "rec/audio/stretch/Stretch.pb.h"
#include "rec/gui/SetterToggle.h"
#include "rec/util/listener/DataListener.h"

namespace rec {

namespace audio { class Gain; }

namespace gui {
namespace audio {

class GainController : public Layout, public DataListener<rec::audio::Gain> {
 public:
  GainController();

  virtual bool isOpaque() const { return true; }

  virtual void setData(persist::Data<rec::audio::Gain>*);
  virtual void operator()(const rec::audio::Gain&);

 private:
  DataSlider<float> level_;
  gui::SetterToggle muteButton_;
  gui::SetterToggle dimButton_;

  DISALLOW_COPY_AND_ASSIGN(GainController);
};

}  // namespace audio
}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_AUDIO_GAINCONTROLLER__
