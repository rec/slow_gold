#include "rec/slow/AboutWindow.h"

#include "rec/gui/SetterToggle.h"
#include "rec/slow/GuiSettings.pb.h"
#include "rec/slow/SlowWindow.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {
namespace slow {

namespace {

using namespace juce;

const int WIDTH = 650;
const int HEIGHT = 350;
const int FADE_IN_TIME = 1200;
const int MARGIN = 20;
const int OFFSET = 150;
const int BUTTON_HEIGHT = 20;
const int BUTTON_WIDTH = 20;
const String BUTTON_TEXT = "Display this window on startup";

static const String LEFT_STRING =
  "* Drag audio files onto the waveform.\n"
  "* CDs will automatically appear in the top-left when you insert them.\n"
  "* Press the space bar to start and stop playback.\n"
  "* Drag the Speed slider to slow down or speed up.\n"
  "* Create loop points by pressing the L key.\n"
  "* Download the manual from the Help menu for many more commands.\n";

}  // namespace

class AboutPane : public Component {
 public:
  AboutPane(const String& name, const String& versionNumber)
      : displayOnStartup_(BUTTON_TEXT, getTypeName<GuiSettings>(),
                          data::Address("show_about_on_startup")) {
    right_.setJustification(Justification::bottomRight);
    left_.setJustification(Justification::centredLeft);

    Font font("Ariel", 20, 0);
    left_.append(LEFT_STRING, font);
    String s = name + " " + versionNumber + "\nWorld Wide Woodshed Software\n" +
      String(CharPointer_UTF8("Copyright © 2012\n"));
    right_.append(s, font);

    addChildComponent(&displayOnStartup_);
    displayOnStartup_.setBounds(MARGIN, HEIGHT - MARGIN - BUTTON_HEIGHT,
                                BUTTON_WIDTH, BUTTON_HEIGHT);
  }

  void startListening() {
    displayOnStartup_.startListening();
  }

  void paint(Graphics& g) {
    g.fillAll(Colours::white);
    g.setColour(Colours::red);
    g.drawRect(0, 0, WIDTH, HEIGHT);
    Rectangle<float> area(MARGIN, MARGIN,
                          WIDTH - 2 * MARGIN, HEIGHT - 2 * MARGIN);
    right_.draw(g, area);
    area.setY(area.getY() + OFFSET);
    left_.draw(g, area);
  }

 private:
  AttributedString left_, right_;
  gui::SetterToggle displayOnStartup_;
};

AboutWindow::AboutWindow(Component* parent,
                         Instance* instance,
                         const String& name,
                         const String& versionNumber)
    : Component("AboutWindow"),
      HasInstance(instance),
      parent_(parent),
      aboutPane_(new AboutPane(name, versionNumber)) {
  setOpaque(false);
  Rectangle<int> bounds = parent_->getLocalBounds();
  setBounds(bounds);
  addAndMakeVisible(aboutPane_.get());
  aboutPane_->setBounds((bounds.getWidth() - WIDTH) / 2,
                      (bounds.getHeight() - HEIGHT) / 2,
                      WIDTH, HEIGHT);
  aboutPane_->setColour(Label::backgroundColourId, Colours::white);
  aboutPane_->setColour(Label::outlineColourId, Colours::red);

  setAlpha(0.0f);
  parent_->addAndMakeVisible(this);
  Desktop::getInstance().getAnimator().fadeIn(this, 2000);
  aboutPane_->addMouseListener(this, true);
  aboutPane_->startListening();
}

AboutWindow::~AboutWindow() {
  Desktop::getInstance().getAnimator().fadeOut(this, 1000);
  getParentComponent()->removeChildComponent(this);
}

void AboutWindow::mouseDown(const MouseEvent&) {
  thread::callAsync(window(), &SlowWindow::stopAboutWindow);
}

}  // namespace slow
}  // namespace rec

