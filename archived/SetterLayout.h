#ifndef __REC_GUI_SETTERLAYOUT__
#define __REC_GUI_SETTERLAYOUT__

#include "rec/gui/Layout.h"

namespace rec {
namespace gui {

class SetterLayout {
 public:
  SetterLayout(const String& name = String::empty,
               Orientation o = HORIZONTAL,
               bool resizeOther = true) : Layout(n, o, resizeOther) {
  }

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(SetterLayout);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_SETTERLAYOUT__
