#ifndef __REC_GUI_COLORS__
#define __REC_GUI_COLORS__

#include <unordered_map>

#include "rec/base/base.h"
#include "rec/gui/Color.pb.h"

namespace rec {
namespace gui {
namespace color {

typedef std::unordered_map<string, Colour> ColourMap;

Colour get(const Colors& colors, int index);

Colour makeColour(const Color&, const ColourMap&);

}  // namespace color
}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_COLORS__#ifndef __REC_GUI_COLORS__
