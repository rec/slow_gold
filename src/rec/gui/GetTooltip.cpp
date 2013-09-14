#include "rec/gui/GetTooltip.h"

using namespace juce;

namespace rec {
namespace gui {

String getTooltip(Component* c) {
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

}  // namespace gui
}  // namespace rec
