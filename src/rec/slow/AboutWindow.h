#ifndef __REC_SLOW_ABOUTWINDOW__
#define __REC_SLOW_ABOUTWINDOW__

#include "rec/gui/SimpleLabel.h"
#include "rec/slow/Instance.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {
namespace slow {

class AboutWindow : public Component, public HasInstance {
 public:
  static const int WIDTH = 400;
  static const int HEIGHT = 400;
  static const int FADE_IN_TIME = 2000;
  static const int FADE_OUT_TIME = 1000;

  explicit AboutWindow(Component* parent, Instance* instance,
                       const String& versionNumber = String::empty)
      : Component("AboutWindow"),
        HasInstance(instance),
        parent_(parent),
        content_("AboutContent"),
        versionNumber_(versionNumber) {
    setOpaque(false);
    juce::Rectangle<int> bounds = parent_->getLocalBounds();
    setBounds(bounds);
    addAndMakeVisible(&content_);
    content_.setBounds((bounds.getWidth() - WIDTH) / 2,
                       (bounds.getHeight() - HEIGHT) / 2,
                       WIDTH, HEIGHT);
    content_.setColour(juce::Label::backgroundColourId, juce::Colours::white);
    content_.setColour(juce::Label::outlineColourId, juce::Colours::red);

    String text = juce::CharPointer_UTF8("SlowGold 8.0\nWorld Wide Woodshed "
                                         "Software\nCopyright © 2011\n") +
      "Version: " + versionNumber_;

    content_.setText(text, false);
    setAlpha(0.0f);
    parent_->addAndMakeVisible(this);
    juce::Desktop::getInstance().getAnimator().fadeIn(this, 2000);
    content_.addMouseListener(this, true);
  }

  virtual void paint(Graphics&) {}

  ~AboutWindow() {
    juce::Desktop::getInstance().getAnimator().fadeOut(this, 1000);
    getParentComponent()->removeChildComponent(this);
  }

  virtual void mouseDown(const MouseEvent&) {
    thread::callAsync(window(), &SlowWindow::stopAboutWindow);
  }

 private:
  Component* parent_;
  gui::SimpleLabel content_;
  String versionNumber_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(AboutWindow);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_ABOUTWINDOW__
