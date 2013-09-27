#ifndef __REC_SLOW_GUILISTENER__
#define __REC_SLOW_GUILISTENER__

#include "rec/data/DataListener.h"
#include "rec/gui/audio/CommandBar.h"
#include "rec/util/StateListener.h"

namespace rec {
namespace slow {

class GuiSettings;

class GuiListener : public DataListener<GuiSettings>,
                    public StateListener<gui::audio::CommandBarCommand> {
 public:
  GuiListener();
  virtual ~GuiListener() {}

  virtual void operator()(const GuiSettings&);
  virtual void operator()(gui::audio::CommandBarCommand);
  virtual void update();

 private:
  CriticalSection lock_;
  unique_ptr<juce::TooltipWindow> tooltipWindow_;
  bool displayHelpPane_;
  Component* lastComponent_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(GuiListener);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_GUILISTENER__
