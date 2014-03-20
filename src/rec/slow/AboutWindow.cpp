#include "rec/slow/AboutWindow.h"

#include "rec/app/AuthenticationDialog.h"
#include "rec/base/Trans.h"
#include "rec/gui/SetterToggle.h"
#include "rec/slow/GuiSettings.pb.h"
#include "rec/slow/Instance.h"
#include "rec/slow/SlowWindow.h"
#include "rec/util/GetEnv.h"
#include "rec/util/thread/CallAsync.h"

TRAN(DISPLAY_ON_STARTUP, "Display this window on startup");
TRAN(DISPLAY_ON_STARTUP_TOOLTIP, "Turn this box on if you want About Slow "
       "Gold to appear on startup.");
TRAN(DRAG_AUDIO, "Drag audio files onto the waveform.");
TRAN(CD_AUTOMATIC, "CDs will automatically appear at the top-left when you "
       "insert them.");
TRAN(PRESS_SPACE, "Press the space bar to start and stop playback.");
TRAN(DRAG_SPEED, "Drag the Speed slider to slow down or speed up.");
TRAN(CREATE_LOOPS, "Create loop points by pressing the L key.");
TRAN(DOWNLOAD_MANUAL, "Download the manual from the Help menu for many more "
       "commands.");
TRAN(COPYRIGHT, "Copyright © %d-%d");
TRAN(REGISTERED_TO, "Registered to:");
TRAN(UNREGISTERED, "Not Registered!");

namespace rec {
namespace slow {

namespace {

// Skin

using namespace juce;

const int WIDTH = 650;
const int HEIGHT = 350;
const int MARGINI = 20;
const float MARGINF = static_cast<float>(MARGINI);
const int OFFSET = 150;
const int BUTTON_HEIGHT = 20;
const int BUTTON_WIDTH = 250;


Font aboutFont() {
  return Font("Ariel", 20, 0);
}

AttributedString getRightSide() {
  auto font = aboutFont();
  AttributedString right;
  right.setJustification(Justification::topRight);
  auto name = JUCEApplication::getInstance()->getApplicationName();
  auto version = JUCEApplication::getInstance()->getApplicationVersion();
  auto t = name + " " + version + "\nWorld Wide Woodshed Software\n" +
      String::formatted(t_COPYRIGHT, 2012, 2014) + String("\n");
  right.append(t, font);

  auto user = getEnv("USERNAME", "");
  auto reg = user.isEmpty() ? String(t_UNREGISTERED) :
    (String("\n") + t_REGISTERED_TO + String(" ") + user);
  right.append(reg, font);
  return right;
}

AttributedString getLeftSide() {
  AttributedString left;
  left.setJustification(Justification::topLeft);
  auto s =
      str("* " + t_DRAG_AUDIO + "\n" +
          "* " + t_CD_AUTOMATIC + "\n" +
          "* " + t_PRESS_SPACE + "\n" +
          "* " + t_DRAG_SPEED + "\n" +
          "* " + t_CREATE_LOOPS + "\n" +
          "* " + t_DOWNLOAD_MANUAL + "\n");
  left.append(s, aboutFont());
  return left;
}

}  // namespace

class AboutPane : public Component {
 public:
  AboutPane(const String& name, const String& versionNumber)
      : displayOnStartup_(
            str(t_DISPLAY_ON_STARTUP),
            str(t_DISPLAY_ON_STARTUP_TOOLTIP),
            data::makeAddress<GuiSettings>("show_about_on_startup")) {
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

  void visibilityChanged() override {
    auto authentication = app::testAuthenticated();
    right_ = getRightSide();
    left_ = getLeftSide();
  }


 private:
  AttributedString left_, right_;
  gui::SetterToggle displayOnStartup_;
};

AboutWindow::AboutWindow(Component* parent,
                         const String& name,
                         const String& versionNumber)
    : Component("AboutWindow"),
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
  if (auto window = getInstance()->window_)
    window->stopAboutWindow();
}

}  // namespace slow
}  // namespace rec
