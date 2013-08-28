#include "rec/gui/LookAndFeel.h"
#include "rec/util/Binary.h"

namespace rec {
namespace gui {

LookAndFeel::LookAndFeel()
#if JUCE_MAC
    : open_(BINARY_DATA(MacFolderOpenButton_svg, Drawable)),
      close_(BINARY_DATA(MacFolderOpenButton_svg, Drawable))
#endif
{
}

#if JUCE_MAC
void LookAndFeel::drawTreeviewPlusMinusBox(Graphics& g, int x, int y, int w,
                                           int h, bool isPlus,
                                           bool isMouseOver) {
  static const int PAD_X = 5;
  static const int PAD_Y = 5;

  juce::Rectangle<float> bounds(x + PAD_X, y + PAD_Y,
                                w - 2 * PAD_X, h - 2 * PAD_Y);
  (isPlus ? open_ : close_)->drawWithin(g, bounds,
                                        juce::RectanglePlacement::stretchToFit,
                                        1.0f);
}
#endif  // JUCE_MAC

}  // namespace gui
}  // namespace rec
