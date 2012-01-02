#include "rec/gui/LookAndFeel.h"
#include "rec/gui/icon/MacFolderCloseButton.svg.h"
#include "rec/gui/icon/MacFolderOpenButton.svg.h"

namespace rec {
namespace gui {

LookAndFeel::LookAndFeel()
#if JUCE_MAC
    : open_(icon::MacFolderOpenButton::create()),
      close_(icon::MacFolderCloseButton::create())
#endif
{
}

void LookAndFeel::drawTreeviewPlusMinusBox(Graphics& g, int x, int y, int w,
                                           int h, bool isPlus,
                                           bool isMouseOver) {
#if JUCE_MAC
  static const int PAD_X = 5;
  static const int PAD_Y = 5;

  juce::Rectangle<float> bounds(x + PAD_X, y + PAD_Y,
                                w - 2 * PAD_X, h - 2 * PAD_Y);
  (isPlus ? open_ : close_)->drawWithin(g, bounds,
                                        juce::RectanglePlacement::stretchToFit,
                                        1.0f);
#endif  // JUCE_MAC
}

}  // namespace gui
}  // namespace rec
