#ifndef __REC_GUI_GETTOOLTIP__
#define __REC_GUI_GETTOOLTIP__

#include "rec/base/base.h"

namespace rec {
namespace gui {

String getTooltip(Component* c);

inline Component* getComponentUnderMouse() {
  return Desktop::getInstance().getMainMouseSource().getComponentUnderMouse();
}

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_GETTOOLTIP__