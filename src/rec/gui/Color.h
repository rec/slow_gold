#ifndef __REC_GUI_COLORS__
#define __REC_GUI_COLORS__

#include "rec/base/base.h"
#include "rec/gui/Color.pb.h"

namespace rec {
namespace gui {
namespace color {

Colour get(const Colors& colors, int index);
const Colors& getDefaultColors();

Colour makeColour(const Color& color);

}  // namespace color
}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_COLORS__
