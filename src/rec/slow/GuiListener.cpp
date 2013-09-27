#include "rec/slow/GuiListener.h"

#include "rec/util/StateListener.h"
#include "rec/gui/GuiWriteable.h"
#include "rec/program/JuceModel.h"
#include "rec/slow/Components.h"
#include "rec/slow/GuiSettings.pb.h"
#include "rec/slow/Instance.h"
#include "rec/slow/MainPage.h"
#include "rec/slow/SlowWindow.h"
#include "rec/slow/commands/Command.pb.h"
#include "rec/gui/GetHelpText.h"
#include "rec/util/thread/CallAsync.h"

using namespace juce;
using namespace rec::command;
using namespace rec::gui::audio;

namespace rec {
namespace slow {

namespace {

inline void invokeAndCheck(CommandID id) {
  program::juceModel()->invokeAndCheck(id);
}

const int MS_TILL_TOOLTIP = 350;

}  // namespace

GuiListener::GuiListener()
    : displayHelpPane_(false), lastComponent_(nullptr) {
}

void GuiListener::operator()(const GuiSettings& settings) {
  if (!settings.show_tooltips())
    tooltipWindow_.reset();
  else if (!tooltipWindow_)
    tooltipWindow_.reset(new TooltipWindow(nullptr, MS_TILL_TOOLTIP));

  Lock l(lock_);
  displayHelpPane_ = settings.show_help_pane();
}

void GuiListener::operator()(CommandBarCommand command) {
  if (command == ADD_LOOP_POINT)
    invokeAndCheck(Command::ADD_LOOP_POINT);

  else if (command == ZOOM_OUT_FULL)
    invokeAndCheck(Command::ZOOM_OUT_FULL);

  else if (command == ZOOM_TO_SELECTION)
    invokeAndCheck(Command::ZOOM_TO_SELECTION);
}

void GuiListener::update() {
  gui::GuiWriteable::writeAll();
  {
    Lock l(lock_);
    if (!displayHelpPane_)
      return;
  }
  gui::refreshHelpText();
}

}  // namespace slow
}  // namespace rec
