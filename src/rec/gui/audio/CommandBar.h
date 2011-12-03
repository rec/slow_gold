#ifndef __REC_GUI_AUDIO_COMMANDBAR__
#define __REC_GUI_AUDIO_COMMANDBAR__

#include "rec/command/Command.h"
#include "rec/gui/layout/Layout.h"
#include "rec/util/DataListener.h"

namespace rec {
namespace gui {
namespace audio {

class CommandBar : public Layout,
                   public Broadcaster<CommandID>,
                   public juce::Button::Listener {
 public:
  CommandBar();
  virtual ~CommandBar() {}

  virtual void buttonClicked(juce::Button*);

 private:
  DrawableButton addLoopPoint_;
  DrawableButton addLoopPointClick_;
  DrawableButton zoomOut_;
  DrawableButton zoomToSelection_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(CommandBar);
};

}  // namespace audio
}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_AUDIO_COMMANDBAR__
