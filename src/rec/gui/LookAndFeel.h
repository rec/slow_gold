#ifndef __REC_GUI_LOOKANDFEEL__
#define __REC_GUI_LOOKANDFEEL__

#include "rec/base/base.h"

namespace rec {
namespace gui {

class LookAndFeel : public juce::LookAndFeel {
 public:
  LookAndFeel();
  virtual ~LookAndFeel() {}

#if JUCE_MAC
  virtual void drawTreeviewPlusMinusBox(Graphics& g, int x, int y, int w,
                                        int h, bool isPlus, bool isMouseOver);

 private:
  ptr<juce::Drawable> open_;
  ptr<juce::Drawable> close_;
#endif

 private:
  DISALLOW_COPY_ASSIGN_AND_LEAKS(LookAndFeel);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_LOOKANDFEEL__
