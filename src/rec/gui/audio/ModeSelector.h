#ifndef __REC_GUI_AUDIO_MODESELECTOR__
#define __REC_GUI_AUDIO_MODESELECTOR__

#include <map>

#include "rec/gui/layout/Layout.h"
#include "rec/util/DataListener.h"
#include "rec/util/Mode.pb.h"

namespace rec {
namespace gui {
namespace audio {

class ModeSelector : public Layout,
                     public juce::Button::Listener,
                     public DataListener<Mode> {
 public:
  ModeSelector();
  virtual ~ModeSelector() {}

  virtual void buttonClicked(juce::Button* button);
  virtual bool isOpaque() const { return true; }

  virtual void onDataChange(const Mode&);
  DrawableButton* getButton(const Mode::Action&);

  typedef std::map<Mode::Action, DrawableButton*> ButtonMap;
  ButtonMap* buttonMap() { return &buttons_; }

 private:
  DrawableButton drag_;
  DrawableButton setTime_;
  DrawableButton toggleSelection_;
  DrawableButton zoomIn_;

  ButtonMap buttons_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(ModeSelector);
};

}  // namespace audio
}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_AUDIO_MODESELECTOR__
