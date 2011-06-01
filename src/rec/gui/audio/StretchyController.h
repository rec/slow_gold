#ifndef __REC_GUI_AUDIO_STRETCHYCONTROLLER__
#define __REC_GUI_AUDIO_STRETCHYCONTROLLER__

#include "rec/gui/DataSlider.h"
#include "rec/gui/Layout.h"
#include "rec/audio/stretch/Stretch.pb.h"
#include "rec/gui/SetterToggle.h"
#include "rec/util/listener/DataListener.h"

namespace rec {
namespace gui {
namespace audio {

class StretchyController : public Layout, public juce::ComboBox::Listener,
                           public DataListener<rec::audio::source::StereoProto>,
                           public DataListener<rec::audio::stretch::Stretch> {
 public:
  StretchyController();
  virtual bool isOpaque() const { return true; }

  virtual void setData(persist::Data<rec::audio::stretch::Stretch>*);
  virtual void setData(persist::Data<rec::audio::source::StereoProto>*);
  virtual void operator()(const rec::audio::stretch::Stretch&);
  virtual void operator()(const rec::audio::source::StereoProto&);

  void setZoom(data::UntypedData* zoom);
  void enableSliders(bool enabled);
  virtual void comboBoxChanged(juce::ComboBox*);

 private:
  DataSlider<double> playbackSpeed_;
  DataSlider<double> pitchScale_;
  DataSlider<double> fineScale_;
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
