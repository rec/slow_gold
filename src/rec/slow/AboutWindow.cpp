#include "rec/slow/AboutWindow.h"

#include "rec/base/Trans.h"
#include "rec/gui/SetterToggle.h"
#include "rec/slow/GuiSettings.pb.h"
#include "rec/slow/SlowWindow.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {
namespace slow {

namespace {

// Skin

Trans DISPLAY_ON_STARTUP("Display this window on startup");
Trans DRAG_AUDIO("Drag audio files onto the waveform.");
Trans CD_AUTOMATIC("CDs will automatically appear in the top-left when you "
                   "insert them.");
Trans PRESS_SPACE("Press the space bar to start and stop playback.");
Trans DRAG_SPEED("Drag the Speed slider to slow down or speed up.");
Trans CREATE_LOOPS("Create loop points by pressing the L key.");
Trans DOWNLOAD_MANUAL("Download the manual from the Help menu for many more "
                      "commands.");
Trans COPYRIGHT("Copyright © %d");

using namespace juce;

const int WIDTH = 650;
const int HEIGHT = 350;
const int MARGIN = 20;
const int OFFSET = 150;
const int BUTTON_HEIGHT = 20;
const int BUTTON_WIDTH = 250;

}  // namespace

class AboutPane : public Component {
 public:
  AboutPane(const String& name, const String& versionNumber)
      : displayOnStartup_(DISPLAY_ON_STARTUP,
                          getTypeName<GuiSettings>(),
                          data::Address("show_about_on_startup"),
                          GLOBAL_SCOPE) {
#if 0
    // FIX JUCE BUG!
    right_.setJustification(Justification::bottomRight);
    left_.setJustification(Justification::centredLeft);
#else
    right_.setJustification(Justification::topRight);
    left_.setJustification(Justification::topLeft);
#endif

    Font font("Ariel", 20, 0);
    String s =
      str("* " + DRAG_AUDIO + "\n" +
          "* " + CD_AUTOMATIC + "\n" +
          "* " + PRESS_SPACE + "\n" +
          "* " + DRAG_SPEED + "\n" +
          "* " + CREATE_LOOPS + "\n" +
          "* " + DOWNLOAD_MANUAL + "\n");

    left_.append(s, font);
    String t = name + " " + versionNumber + "\nWorld Wide Woodshed Software\n" +
      String::formatted(COPYRIGHT, 2012);
    right_.append(t, font);

    addAndMakeVisible(&displayOnStartup_);
    displayOnStartup_.setBounds(MARGIN, HEIGHT - MARGIN - BUTTON_HEIGHT,
                                BUTTON_WIDTH, BUTTON_HEIGHT);
    setOpaque(true);
    displayOnStartup_.setInterceptsMouseClicks(true, true);
  }

  void init() {
    displayOnStartup_.init();
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
  aboutPane_->addMouseListener(this, false);
  aboutPane_->init();
}

AboutWindow::~AboutWindow() {}

void AboutWindow::mouseDown(const MouseEvent&) {
  if (window())
    thread::callAsync(window(), &SlowWindow::stopAboutWindow);
}

void AboutWindow::translateAll() {
  DISPLAY_ON_STARTUP.translate();
  DRAG_AUDIO.translate();
  CD_AUTOMATIC.translate();
  PRESS_SPACE.translate();
  DRAG_SPEED.translate();
  CREATE_LOOPS.translate();
  DOWNLOAD_MANUAL.translate();
  COPYRIGHT.translate();
}

}  // namespace slow
}  // namespace rec

