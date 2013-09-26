#include "rec/gui/GetHelpText.h"
#include "rec/data/DataBroadcaster.h"

using namespace juce;

namespace rec {
namespace gui {

namespace {

HelpText getHelpText(Component* c);

inline Component* getComponentUnderMouse() {
  return Desktop::getInstance().getMainMouseSource().getComponentUnderMouse();
}

HelpText splitHelpText(const String& tt) {
  std::pair<String, String> result;
  int pos = tt.indexOf(":");
  if (pos == -1) {
    result.second = tt;
  } else {
    result.first = tt.substring(0, pos).trim();
    result.second = tt.substring(pos + 1).trim();
  }
  return result;
}

String getHelpTextFromComponent(Component* c) {
  String result;
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

Component* COMPONENT = nullptr;

}  // namespace

void refreshHelpText() {
  Component* comp = getComponentUnderMouse();
  if (comp != COMPONENT) {
    COMPONENT = comp;
    data::broadcastData<const HelpText&>(
        splitHelpText(getHelpTextFromComponent(comp)));
  }
}

}  // namespace gui
}  // namespace rec
