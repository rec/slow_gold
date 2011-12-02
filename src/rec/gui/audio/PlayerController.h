#ifndef __REC_GUI_AUDIO_PLAYERCONTROLLER__
#define __REC_GUI_AUDIO_PLAYERCONTROLLER__

#include "rec/audio/stretch/Stretch.pb.h"
#include "rec/gui/DataSlider.h"
#include "rec/gui/SetterToggle.h"
#include "rec/audio/util/Gain.h"
#include "rec/gui/audio/LevelMeter.h"
#include "rec/gui/layout/Layout.h"
#include "rec/util/DataListener.h"
#include "rec/util/Mode.pb.h"
#include "rec/widget/waveform/Zoom.pb.h"

namespace rec {
namespace gui {
namespace audio {

class PlayerController : public Layout, public juce::ComboBox::Listener,
                         public DataListener<rec::audio::Gain>,
                         public DataListener<rec::audio::source::StereoProto>,
                         public DataListener<rec::audio::stretch::Stretch> {
 public:
  PlayerController();
  virtual ~PlayerController() {}

  virtual bool isOpaque() const { return true; }

  virtual void onDataChange(const rec::audio::stretch::Stretch&);
  virtual void onDataChange(const rec::audio::source::StereoProto&);
  virtual void onDataChange(const rec::audio::Gain&);

  virtual void comboBoxChanged(juce::ComboBox*);

  listener::Listener<const LevelVector&>* levelListener() { return &levelMeter_; }
  void clearLevels();
  LevelMeter* levelMeter() { return &levelMeter_; }

 private:
  DataSlider<rec::audio::stretch::Stretch, double> playbackSpeed_;
  DataSlider<rec::audio::stretch::Stretch, double> pitchScale_;
  DataSlider<rec::audio::stretch::Stretch, double> fineScale_;
  DataSlider<rec::audio::Gain, double> level_;

  LevelMeter levelMeter_;

  gui::SetterToggle<rec::audio::Gain> muteButton_;

  juce::ComboBox stereoComboBox_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(PlayerController);
};

}  // namespace audio
}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_AUDIO_PLAYERCONTROLLER__
