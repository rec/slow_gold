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

void GuiListener::operator()(const GuiSettings& settings) {
  if (!settings.show_tooltips()) {
    tooltipWindow_.reset();

  } else if (!tooltipWindow_) {
    MessageManagerLock l;
    tooltipWindow_.reset(new TooltipWindow(NULL, MS_TILL_TOOLTIP));
  }

  Lock l(lock_);
  displayHelpPane_ = settings.show_help_pane();
}

static String getTooltip(Component* c) {
  while (c) {
    if (TooltipClient* ttc = dynamic_cast<TooltipClient*>(c)) {
      const String& s = ttc->getTooltip();
      if (s.length())
       return s;
    }
    c = c->getParentComponent();
  }
  return "";
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
    String s = getTooltip(comp);
    MessageManagerLock l;
    components()->mainPage_->setTooltip(s);
  }
}

}  // namespace slow
}  // namespace rec
