#ifndef __REC_SLOW_GUILISTENER__
#define __REC_SLOW_GUILISTENER__

#include "rec/slow/Components.h"
#include "rec/slow/HasInstance.h"
#include "rec/slow/MainPage.h"
#include "rec/slow/SlowWindow.h"
#include "rec/util/DataListener.h"

namespace rec {
namespace slow {

class GuiListener : public GlobalDataListener<GuiSettings>, public HasInstance {
 public:
  explicit GuiListener(Instance* i) : HasInstance(i),
                                      displayHelpPane_(false),
                                      lastComponent_(NULL) {}

  static const int MS_TILL_TOOLTIP = 700;
  virtual void onDataChange(const GuiSettings& settings) {
    { 
      MessageManagerLock l;
      if (!settings.show_tooltips()) 
        tooltipWindow_.reset();
      else if (!tooltipWindow_)
        tooltipWindow_.reset(new juce::TooltipWindow(NULL, MS_TILL_TOOLTIP));
    }

    Lock l(lock_);
    displayHelpPane_ = settings.show_help_pane();
  }

  virtual void update() {
    window()->writeGui();
    {
      Lock l(lock_);
      if (!displayHelpPane_)
        return;
    }
    Component* comp = juce::Desktop::getInstance().
      getMainMouseSource().getComponentUnderMouse();
      
    if (comp != lastComponent_) {
      lastComponent_ = comp;
      juce::TooltipClient* const ttc = dynamic_cast<juce::TooltipClient*>(comp);
      MessageManagerLock l;
      components()->mainPage_->setTooltip(ttc ? ttc->getTooltip() : String::empty);
    }
  }

 private:
  CriticalSection lock_;
  ptr<juce::TooltipWindow> tooltipWindow_;
  bool displayHelpPane_;
  Component* lastComponent_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(GuiListener);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_GUILISTENER__
