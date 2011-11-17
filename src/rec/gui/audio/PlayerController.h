#ifndef __REC_GUI_AUDIO_PLAYERCONTROLLER__
#define __REC_GUI_AUDIO_PLAYERCONTROLLER__

#include "rec/audio/stretch/Stretch.pb.h"
#include "rec/gui/DataSlider.h"
#include "rec/gui/SetterToggle.h"
#include "rec/audio/util/Gain.h"
#include "rec/gui/audio/LevelMeter.h"
#include "rec/gui/audio/ModeSelector.h"
#include "rec/gui/layout/Layout.h"
#include "rec/util/listener/DataListener.h"
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
  ModeSelector* modeSelector() { return &modeSelector_; }

 private:
  DataSlider<rec::audio::stretch::Stretch, double> playbackSpeed_;
  DataSlider<rec::audio::stretch::Stretch, double> pitchScale_;
  DataSlider<rec::audio::stretch::Stretch, double> fineScale_;
  DataSlider<rec::audio::Gain, double> level_;

  LevelMeter levelMeter_;

  // gui::SetterToggle disableButton_;
  gui::SetterToggle<widget::waveform::ZoomProto> zoomToSelectionButton_;
  gui::SetterToggle<rec::audio::Gain> preFaderLevels_;

  gui::SetterToggle<rec::audio::Gain> muteButton_;
  gui::SetterToggle<rec::audio::Gain> dimButton_;

  juce::ComboBox stereoComboBox_;
  ModeSelector modeSelector_;

  DISALLOW_COPY_AND_ASSIGN(PlayerController);
};

}  // namespace audio
}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_AUDIO_PLAYERCONTROLLER__
