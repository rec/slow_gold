#ifndef __REC_GUI_AUDIO_TRANSFORMCONTROLLER__
#define __REC_GUI_AUDIO_TRANSFORMCONTROLLER__

#include "rec/audio/stretch/Stretch.pb.h"
#include "rec/audio/util/Gain.h"
#include "rec/gui/DataSlider.h"
#include "rec/gui/SetterToggle.h"
#include "rec/gui/layout/Layout.h"
#include "rec/util/DataListener.h"
#include "rec/util/Mode.pb.h"
#include "rec/widget/waveform/Zoom.pb.h"

namespace rec {
namespace gui {
namespace audio {

class TransformController : public Layout,
                            public juce::ComboBox::Listener,
                            public DataListener<rec::audio::source::StereoProto>,
                            public DataListener<rec::audio::stretch::Stretch> {
 public:
  TransformController();
  virtual ~TransformController();

  virtual bool isOpaque() const { return true; }

  virtual void onDataChange(const rec::audio::stretch::Stretch&);
  virtual void onDataChange(const rec::audio::source::StereoProto&);

  virtual void comboBoxChanged(juce::ComboBox*);

 private:
  DataSlider<rec::audio::stretch::Stretch, double> playbackSpeed_;
  DataSlider<rec::audio::stretch::Stretch, double> pitchScale_;
  DataSlider<rec::audio::stretch::Stretch, double> fineScale_;

  gui::SetterToggle<rec::audio::stretch::Stretch> enableButton_;

  juce::ComboBox stereoComboBox_;
  Layout leftPanel_;
  Layout rightPanel_;

  Layout leftPadding_;
  Layout rightPadding_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(TransformController);
};

}  // namespace audio
}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_AUDIO_TRANSFORMCONTROLLER__
