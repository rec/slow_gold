#include "rec/gui/GetTooltip.h"

using namespace juce;

namespace rec {
namespace gui {

namespace {
Tooltip splitTooltip(const String& tt) {
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

String getTooltipFromComponent(Component* c) {
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


}  // namespace

Tooltip getTooltip(Component* c) {
  return splitTooltip(getTooltipFromComponent(c));
}

}  // namespace gui
}  // namespace rec
