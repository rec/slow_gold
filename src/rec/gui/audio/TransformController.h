#ifndef __REC_GUI_AUDIO_TRANSFORMCONTROLLER__
#define __REC_GUI_AUDIO_TRANSFORMCONTROLLER__

#include "rec/app/LanguageListener.h"
#include "rec/audio/stretch/Stretch.pb.h"
#include "rec/audio/util/Gain.h"
#include "rec/audio/source/Stereo.pb.h"
#include "rec/gui/DataSlider.h"
#include "rec/gui/SetterToggle.h"
#include "rec/gui/proto/Panel.h"
#include "rec/data/DataListener.h"
#include "rec/util/Mode.pb.h"
#include "rec/widget/waveform/Zoom.pb.h"

namespace rec {
namespace gui {
namespace audio {

class TransformController : public Panel,
                            public data::DataListener<rec::audio::source::StereoProto>,
                            public data::DataListener<rec::audio::stretch::Stretch>,
                            public app::LanguageListener,
                            public juce::ComboBox::Listener {
 public:
  TransformController();
  virtual ~TransformController();

  virtual bool isOpaque() const { return true; }

  virtual void operator()(const rec::audio::stretch::Stretch&);
  virtual void operator()(const rec::audio::source::StereoProto&);
  virtual void languageChanged();

  virtual void comboBoxChanged(juce::ComboBox*);

 private:
  void setStretch(const rec::audio::stretch::Stretch&);

  gui::SetterToggle enableButton_;

  juce::ComboBox stereoComboBox_;
  Panel leftPanel_;

  Panel leftPadding_;
  unique_ptr<Component> rightPanel_;

  rec::audio::source::StereoProto stereo_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(TransformController);
};

}  // namespace audio
}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_AUDIO_TRANSFORMCONTROLLER__
