#include "rec/slow/AboutWindow.h"

#include "rec/slow/SlowWindow.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {
namespace slow {

namespace {

const int WIDTH = 400;
const int HEIGHT = 400;
const int FADE_IN_TIME = 1200;

}  // namespace

AboutWindow::AboutWindow(Component* parent,
                         Instance* instance,
                         const String& name,
                         const String& versionNumber)
    : Component("AboutWindow"),
      HasInstance(instance),
      parent_(parent),
      content_("AboutContent") {
  setOpaque(false);
  juce::Rectangle<int> bounds = parent_->getLocalBounds();
  setBounds(bounds);
  addAndMakeVisible(&content_);
  content_.setBounds((bounds.getWidth() - WIDTH) / 2,
                     (bounds.getHeight() - HEIGHT) / 2,
                     WIDTH, HEIGHT);
  content_.setColour(juce::Label::backgroundColourId, juce::Colours::white);
  content_.setColour(juce::Label::outlineColourId, juce::Colours::red);

  String text = name + " " + versionNumber +
    "\nWorld Wide Woodshed Software\n" +
    String(juce::CharPointer_UTF8("Copyright © 2012\n"));

  content_.setText(text, false);
  setAlpha(0.0f);
  parent_->addAndMakeVisible(this);
  juce::Desktop::getInstance().getAnimator().fadeIn(this, 2000);
  content_.addMouseListener(this, true);
}

AboutWindow::~AboutWindow() {
  juce::Desktop::getInstance().getAnimator().fadeOut(this, 1000);
  getParentComponent()->removeChildComponent(this);
}

void AboutWindow::mouseDown(const MouseEvent&) {
  thread::callAsync(window(), &SlowWindow::stopAboutWindow);
}

}  // namespace slow
}  // namespace rec

