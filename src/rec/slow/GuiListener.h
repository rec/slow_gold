#ifndef __REC_SLOW_GUILISTENER__
#define __REC_SLOW_GUILISTENER__

#include "rec/slow/HasInstance.h"
#include "rec/data/DataListener.h"

namespace rec {
namespace slow {

class GuiSettings;

class GuiListener : public GlobalDataListener<GuiSettings>, public HasInstance {
 public:
  explicit GuiListener(Instance* i);

  virtual void operator()(const GuiSettings&);
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
