#ifndef __REC_GUI_FOCUSABLE__
#define __REC_GUI_FOCUSABLE__

#include "rec/base/base.h"

namespace rec {
namespace gui {

inline void paintFocus(Graphics& g, Component* c, int reduction = 0) {
  if (c->hasKeyboardFocus(true)) {
    g.setColour(juce::Colours::red.withAlpha(0.8f));
    g.drawRect(c->getLocalBounds().reduced(reduction, reduction));
  }
}

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_FOCUSABLE__
