#ifndef __REC_GUI_COLORS__
#define __REC_GUI_COLORS__

#include "rec/base/base.h"
#include "rec/gui/Color.pb.h"
#include "JuceLibraryCode/JuceHeader.h"

namespace rec {
namespace gui {
namespace color {

Colour get(unsigned int i);
Colour get(const Colors& colors, unsigned int index);
void prepare(const Colors& colors, Graphics* g);

}  // namespace color
}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_COLORS__
