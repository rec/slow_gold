#include "rec/slow/AboutWindow.h"

#include "rec/app/AuthenticationDialog.h"
#include "rec/base/Trans.h"
#include "rec/gui/SetterToggle.h"
#include "rec/slow/GuiSettings.pb.h"
#include "rec/slow/Instance.h"
#include "rec/slow/SlowWindow.h"
#include "rec/util/GetEnv.h"
#include "rec/util/thread/CallAsync.h"

using namespace juce;
using namespace rec::app;

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
TRAN(REGISTERED_TO, "Registered To:");
TRAN(SERIAL_NUMBER, "Serial Number:");
TRAN(UNREGISTERED, "Not Registered!");
TRAN(NAME_LABEL, "Name");
TRAN(SERIAL_NUMBER_LABEL, "Serial Number");
TRAN(REGISTER_TEXT, "Register");

namespace rec {
namespace slow {

namespace {

const int WIDTH = 650;
const int HEIGHT = 350;
const int MARGINI = 12;
const float MARGINF = static_cast<float>(MARGINI);
const int OFFSET = 180;
const int BUTTON_HEIGHT = 20;
const int BUTTON_WIDTH = 250;

Font aboutFont() {
  return Font("Ariel", 20, 0);
}

}  // namespace

class AboutPane : public Component {
 public:
  AboutPane(const String& name, const String& versionNumber)
      : displayOnStartup_(
            str(t_DISPLAY_ON_STARTUP),
            str(t_DISPLAY_ON_STARTUP_TOOLTIP),
            data::makeAddress<GuiSettings>("show_about_on_startup")),
        accept_(t_REGISTER_TEXT) {
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
    authentication_ = testAuthenticated();
    right_ = getRightSide();
    left_ = getLeftSide();
  }

  bool expired() const { return authentication_.expired(); }

  AttributedString getRightSide() const {
    auto font = aboutFont();
    AttributedString right;
    right.setJustification(Justification::topRight);
    auto name = JUCEApplication::getInstance()->getApplicationName();
    auto version = JUCEApplication::getInstance()->getApplicationVersion();
    auto t = name + " " + version + "\nWorld Wide Woodshed Software\n" +
        String::formatted(t_COPYRIGHT, 2012, 2014) + String("\n");
    right.append(t, font);

    String user = authentication_.user;
    if (user.isEmpty()) {
      right.append(t_UNREGISTERED, font);
    } else {
      right.append(String("\n") + t_REGISTERED_TO + String(" ") + user +
                   String("\n") + t_SERIAL_NUMBER + String(" ") +
                   authentication_.serialNumber, font);
    }
    return right;
  }

  AttributedString getLeftSide() const {
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

 private:
  AttributedString left_, right_;
  gui::SetterToggle displayOnStartup_;
  Authentication authentication_;
  TextEditor name_, serialNumber_;
  TextButton accept_;
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
  if (not aboutPane_->expired()) {
    if (auto window = getInstance()->window_)
      window->stopAboutWindow();
  }
}

}  // namespace slow
}  // namespace rec
