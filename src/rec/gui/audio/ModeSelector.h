#ifndef __REC_GUI_AUDIO_MODESELECTOR__
#define __REC_GUI_AUDIO_MODESELECTOR__

#include <map>

#include "rec/gui/proto/Panel.h"
#include "rec/gui/HasSizeHints.h"
#include "rec/gui/LanguageButton.h"
#include "rec/data/DataListener.h"
#include "rec/util/Mode.pb.h"

namespace rec {
namespace gui {
namespace audio {

class ModeSelector : public Panel,
                     public DataListener<Mode>,
                     public juce::Button::Listener {
 public:
  ModeSelector();
  virtual ~ModeSelector() {}

  virtual void buttonClicked(juce::Button* button);
  virtual bool isOpaque() const { return true; }

  virtual void operator()(const Mode&);
  LanguageButton* getButton(Mode::Action);

  typedef std::map<Mode::Action, LanguageButton*> ButtonMap;
  ButtonMap* buttonMap() { return &buttons_; }

  virtual juce::Point<int> getMinSize() const { return minSize_; }

 private:
  void setMode(Mode::Action);

  CriticalSection lock_;

  LanguageButton drag_;
  LanguageButton setTime_;
  LanguageButton zoomIn_;
  LanguageButton addLoopPointClick_;

  juce::Point<int> minSize_;

  ButtonMap buttons_;
  Mode mode_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(ModeSelector);
};

}  // namespace audio
}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_AUDIO_MODESELECTOR__
