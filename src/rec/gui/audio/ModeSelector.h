#ifndef __REC_GUI_AUDIO_MODESELECTOR__
#define __REC_GUI_AUDIO_MODESELECTOR__

#include <map>

#include "rec/app/LanguageListener.h"
#include "rec/gui/layout/Layout.h"
#include "rec/gui/HasSizeHints.h"
#include "rec/data/DataListener.h"
#include "rec/util/Mode.pb.h"

namespace rec {
namespace gui {
namespace audio {

class ModeSelector : public Layout,
                     public GlobalDataListener<Mode>,
                     public app::LanguageListener,
                     public juce::Button::Listener {
 public:
  ModeSelector();
  virtual ~ModeSelector() {}

  virtual void buttonClicked(juce::Button* button);
  virtual bool isOpaque() const { return true; }

  virtual void languageChanged();
  virtual void operator()(const Mode&);
  DrawableButton* getButton(Mode::Action);

  typedef std::map<Mode::Action, DrawableButton*> ButtonMap;
  ButtonMap* buttonMap() { return &buttons_; }

  virtual juce::Point<int> getMinSize() const { return minSize_; }

 private:
  void setMode(Mode::Action);

  CriticalSection lock_;

  DrawableButton drag_;
  DrawableButton setTime_;
  DrawableButton zoomIn_;
  DrawableButton addLoopPointClick_;

  juce::Point<int> minSize_;

  ButtonMap buttons_;
  Mode mode_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(ModeSelector);
};

}  // namespace audio
}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_AUDIO_MODESELECTOR__
