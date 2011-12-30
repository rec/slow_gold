#ifndef __REC_GUI_ABOUTWINDOW__
#define __REC_GUI_ABOUTWINDOW__

#include "rec/gui/SimpleLabel.h"

namespace rec {
namespace gui {

class AboutWindow : public Component {
 public:
  static const int WIDTH = 300;
  static const int HEIGHT = 300;

  explicit AboutWindow(Component* parent) : Component("AboutWindow"),
                                            parent_(parent),
                                            content_("AboutContent") {
    juce::Rectangle<int> bounds = parent_->getLocalBounds();
    setBounds(bounds);
    addAndMakeVisible(&content_);
    content_.setBounds((bounds.getWidth() - WIDTH) / 2,
                       (bounds.getHeight() - HEIGHT) / 2,
                       WIDTH, HEIGHT);

    content_.setText("SlowGold 8.0\nWorld Wide Woodshed Software\nCopyright © 2011");
    setAlpha(0.0);
    parent_.addAndMakeVisible(this);
    juce::Desktop::getAnimator().fadeIn(this, 5000);
  }

  void finishWindow() {
    juce::Desktop::getAnimator().fadeOut(this, 5000);
  }

 private:
  Component* parent_;
  SimpleLabel content_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(AboutWindow);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_ABOUTWINDOW__
