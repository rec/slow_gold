#ifndef __REC_GUI_AUDIO_COMMANDBAR__
#define __REC_GUI_AUDIO_COMMANDBAR__

#include "rec/gui/LanguageButton.h"
#include "rec/gui/layout/Layout.h"
#include "rec/data/DataListener.h"

namespace rec {
namespace gui {
namespace audio {

enum CommandBarCommand {
  ADD_LOOP_POINT,
  ZOOM_OUT_FULL,
  ZOOM_TO_SELECTION
};

class CommandBar : public Layout,
                   public Broadcaster<CommandBarCommand>,
                   public juce::Button::Listener {
 public:
  CommandBar();
  virtual ~CommandBar() {}

  virtual void buttonClicked(juce::Button*);

 private:
  LanguageButton addLoopPoint_;
  LanguageButton zoomOutFull_;
  LanguageButton zoomToSelection_;
  Layout padding_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(CommandBar);
};

}  // namespace audio
}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_AUDIO_COMMANDBAR__
