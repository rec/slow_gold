#ifndef __REC_GUI_COLORS__
#define __REC_GUI_COLORS__

#include "rec/base/base.h"
#include "rec/gui/Color.pb.h"

namespace rec {
namespace gui {
namespace color {

juce::Colour get(unsigned int i);
juce::Colour get(const Colors& colors, unsigned int index);
void prepare(const Colors& colors, juce::Graphics* g);

juce::Colour makeColour(const Color& color);

}  // namespace color
}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_COLORS__
