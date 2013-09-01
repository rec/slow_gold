#ifndef __REC_SLOW_GUILISTENER__
#define __REC_SLOW_GUILISTENER__

#include "rec/data/DataListener.h"
#include "rec/command/ID.h"
#include "rec/gui/audio/CommandBar.h"
#include "rec/gui/audio/TransportController.h"
#include "rec/slow/HasInstance.h"

namespace rec {
namespace slow {

class GuiSettings;

class GuiListener : public GlobalDataListener<GuiSettings>,
                    public Listener<gui::audio::CommandBarCommand>,
                    public Listener<gui::audio::TransportCommand>,
                    public Broadcaster<command::ID>,
                    public HasInstance {
 public:
  explicit GuiListener(Instance* i);

  virtual void operator()(const GuiSettings&);
  virtual void operator()(gui::audio::TransportCommand);
  virtual void operator()(gui::audio::CommandBarCommand);
  virtual void update();

 private:
  CriticalSection lock_;
  ptr<juce::TooltipWindow> tooltipWindow_;
  bool displayHelpPane_;
  Component* lastComponent_;
  Component* lastFocus_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(GuiListener);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_GUILISTENER__
