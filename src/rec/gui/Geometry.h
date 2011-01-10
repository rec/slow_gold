#ifndef __REC_GUI_GEOMETRY__
#define __REC_GUI_GEOMETRY__

#include "rec/base/base.h"
#include "rec/gui/Geometry.pb.h"

namespace rec {
namespace gui {

void drawLine(Graphics& g, const Line& line,
              float sx, float sy, float ex, float ey);

void drawLine(Graphics& g, const Line& line, const juce::Rectangle<int>& r);

void copy(const Rectangle& from, juce::Rectangle<int>* to);
void copy(const juce::Rectangle<int>& from, Rectangle* to);

juce::Rectangle<int> copy(const Rectangle& rect);
Rectangle copy(const juce::Rectangle<int>& rect);

juce::Rectangle<int> centerSquare(const juce::Rectangle<int>& rect);


}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_GEOMETRY__
