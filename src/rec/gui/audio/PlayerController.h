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

  virtual void setData(persist::Data<rec::audio::stretch::Stretch>*);
  virtual void setData(persist::Data<rec::audio::Gain>*);

  void setZoom(data::UntypedData* zoom);
  void enableSliders(bool enabled);
  virtual void comboBoxChanged(juce::ComboBox*);

  listener::Listener<const LevelVector&>* levelListener() { return &levelMeter_; }
  LevelMeter* levelMeter() { return &levelMeter_; }
  ModeSelector* modeSelector() { return &modeSelector_; }

 private:
  DataSlider<double> playbackSpeed_;
  DataSlider<double> pitchScale_;
  DataSlider<double> fineScale_;
  DataSlider<double> level_;

  LevelMeter levelMeter_;

  gui::SetterToggle disableButton_;
  gui::SetterToggle zoomToSelectionButton_;

  gui::SetterToggle muteButton_;
  gui::SetterToggle dimButton_;

  juce::ComboBox stereoComboBox_;
  ModeSelector modeSelector_;

  DISALLOW_COPY_AND_ASSIGN(PlayerController);
};

}  // namespace audio
}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_AUDIO_PLAYERCONTROLLER__
