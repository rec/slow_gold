#include "rec/slow/GuiListener.h"

#include "rec/slow/Components.h"
#include "rec/slow/GuiSettings.pb.h"
#include "rec/slow/MainPage.h"
#include "rec/slow/SlowWindow.h"

namespace rec {
namespace slow {

using namespace juce;

static const int MS_TILL_TOOLTIP = 700;

GuiListener::GuiListener(Instance* i) : HasInstance(i),
                                        displayHelpPane_(false),
                                        lastComponent_(NULL) {
}

void GuiListener::onDataChange(const GuiSettings& settings) {
  if (!settings.show_tooltips())
    tooltipWindow_.reset();

  else if (!tooltipWindow_)
    tooltipWindow_.reset(new TooltipWindow(NULL, MS_TILL_TOOLTIP));

  Lock l(lock_);
  displayHelpPane_ = settings.show_help_pane();
}

static TooltipClient* getTooltipParent(Component* c) {
  while (c) {
    if (TooltipClient* ttc = dynamic_cast<TooltipClient*>(c))
      return ttc;
    else
      c = c->getParentComponent();
  }
  return NULL;
}

void GuiListener::update() {
  window()->writeGui();
  {
    Lock l(lock_);
    if (!displayHelpPane_)
      return;
  }

  Component* comp = Desktop::getInstance().
    getMainMouseSource().getComponentUnderMouse();

  if (comp != lastComponent_) {
    lastComponent_ = comp;
    TooltipClient* ttc = getTooltipParent(comp);
    MessageManagerLock l;
    components()->mainPage_->setTooltip(ttc ? ttc->getTooltip() : String::empty);
  }
}

}  // namespace slow
}  // namespace rec
