#include "rec/slow/AboutWindow.h"

#include "rec/base/Trans.h"
#include "rec/gui/SetterToggle.h"
#include "rec/slow/GuiSettings.pb.h"
#include "rec/slow/SlowWindow.h"
#include "rec/util/GetEnv.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {
namespace slow {

namespace {

// Skin

TRTR(DISPLAY_ON_STARTUP, "Display this window on startup");
TRTR(DRAG_AUDIO, "Drag audio files onto the waveform.");
TRTR(CD_AUTOMATIC, "CDs will automatically appear at the top-left when you "
                   "insert them.");
TRTR(PRESS_SPACE, "Press the space bar to start and stop playback.");
TRTR(DRAG_SPEED, "Drag the Speed slider to slow down or speed up.");
TRTR(CREATE_LOOPS, "Create loop points by pressing the L key.");
TRTR(DOWNLOAD_MANUAL, "Download the manual from the Help menu for many more "
                      "commands.");
TRTR(COPYRIGHT, "Copyright © %d");
TRTR(REGISTERED_TO, "Registered to:");
TRTR(UNREGISTERED, "Not Registered!");

using namespace juce;

const int WIDTH = 650;
const int HEIGHT = 350;
const int MARGINI = 20;
const float MARGINF = static_cast<float>(MARGINI);
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
      String::formatted(COPYRIGHT, 2012) + String("\n");
    right_.append(t, font);

    String user = getEnv("USERNAME", "");
    String reg = user.isEmpty() ? String(UNREGISTERED) :
      (String("\n") + REGISTERED_TO + String(" ") + user);
    right_.append(reg, font);

    addAndMakeVisible(&displayOnStartup_);
    displayOnStartup_.setBounds(MARGINI, HEIGHT - MARGINI - BUTTON_HEIGHT,
                                BUTTON_WIDTH, BUTTON_HEIGHT);
    setOpaque(true);
    displayOnStartup_.updateCallback();
  }

  void paint(Graphics& g) {
    g.fillAll(Colours::white);
    g.setColour(Colours::red);
    g.drawRect(0, 0, WIDTH, HEIGHT);
    Rectangle<float> area(MARGINF, MARGINF,
                          WIDTH - 2 * MARGINF,
                          HEIGHT - 2 * MARGINF);
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
}

AboutWindow::~AboutWindow() {}

void AboutWindow::mouseDown(const MouseEvent&) {
  if (window())
    window()->stopAboutWindow();
}

void AboutWindow::registerAllTranslations() {
  CD_AUTOMATIC.registerTranslation();
  COPYRIGHT.registerTranslation();
  CREATE_LOOPS.registerTranslation();
  DISPLAY_ON_STARTUP.registerTranslation();
  DOWNLOAD_MANUAL.registerTranslation();
  DRAG_AUDIO.registerTranslation();
  DRAG_SPEED.registerTranslation();
  PRESS_SPACE.registerTranslation();
  REGISTERED_TO.registerTranslation();
  UNREGISTERED.registerTranslation();
}

}  // namespace slow
}  // namespace rec

