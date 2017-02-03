#pragma once

#include "rec/base/base.h"

namespace rec {
namespace gui {

class LookAndFeel : public juce::LookAndFeel_V3 {
 public:
  LookAndFeel();
  virtual ~LookAndFeel() {}

#if JUCE_MAC
  virtual void drawTreeviewPlusMinusBox(Graphics& g, int x, int y, int w,
                                        int h, bool isPlus, bool isMouseOver);

 private:
  std::unique_ptr<juce::Drawable> open_;
  std::unique_ptr<juce::Drawable> close_;
#endif

 private:
  DISALLOW_COPY_ASSIGN_AND_LEAKS(LookAndFeel);
};

}  // namespace gui
}  // namespace rec
