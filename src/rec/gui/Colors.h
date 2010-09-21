#ifndef __REC_GUI_COLORS__
#define __REC_GUI_COLORS__

#include "rec/base/basictypes.h"
#include "rec/gui/Colors.pb.h"
#include "JuceLibraryCode/JuceHeader.h"

namespace rec {
namespace gui {
namespace color {

Colour get(const Colors& colors, unsigned int index);
void set(const Colors& c, unsigned int index, Graphics* g);

}  // namespace color
}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_COLORS__
