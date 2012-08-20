#ifndef __REC_GUI_AUDIO_COMMANDBAR__
#define __REC_GUI_AUDIO_COMMANDBAR__

#include "rec/app/AppSettings.pb.h"
#include "rec/command/Command.h"
#include "rec/gui/layout/Layout.h"
#include "rec/data/DataListener.h"

namespace rec {
namespace gui {
namespace audio {

class CommandBar : public Layout,
                   public Broadcaster<CommandID>,
                   public data::GlobalDataListener<app::AppSettings>,
                   public juce::Button::Listener {
 public:
  CommandBar();
  virtual ~CommandBar() {}

  virtual void buttonClicked(juce::Button*);
  virtual void operator()(const app::AppSettings&);

 private:
  DrawableButton addLoopPoint_;
  DrawableButton zoomOutFull_;
  DrawableButton zoomToSelection_;
  Layout padding_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(CommandBar);
};

}  // namespace audio
}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_AUDIO_COMMANDBAR__
