#ifndef __REC_GUI_AUDIO_STRETCHYCONTROLLER__
#define __REC_GUI_AUDIO_STRETCHYCONTROLLER__

#include "rec/gui/SetterSlider.h"
#include "rec/gui/Layout.h"
#include "rec/audio/stretch/Stretch.pb.h"
#include "rec/gui/SetterToggle.h"
#include "rec/util/listener/DataListener.h"

namespace rec {
namespace gui {
namespace audio {

class StretchyController : public Layout, public juce::ComboBox::Listener,
                           public DataListener<rec::audio::stretch::StretchLoop> {
 public:
  StretchyController();
  virtual bool isOpaque() const { return true; }

  virtual void setData(persist::Data<rec::audio::stretch::StretchLoop>* data);
  virtual void operator()(const rec::audio::stretch::StretchLoop&) {
    // TODO
  }

  void setZoom(data::UntypedData* zoom);
  void enableSliders(bool enabled);
  virtual void comboBoxChanged(juce::ComboBox*);

 private:
  SetterSlider playbackSpeed_;
  SetterSlider pitchScale_;
  SetterSlider fineScale_;
  gui::SetterToggle disableButton_;
  gui::SetterToggle zoomToSelectionButton_;
  gui::SetterToggle clickToZoomButton_;
  juce::ComboBox stereoComboBox_;

  DISALLOW_COPY_AND_ASSIGN(StretchyController);
};

}  // namespace rec
}  // namespace gui
}  // namespace audio

#endif  // __REC_GUI_AUDIO_STRETCHYCONTROLLER__
