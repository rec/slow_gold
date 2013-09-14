#include "rec/slow/GuiListener.h"

#include "rec/gui/GuiWriteable.h"
#include "rec/program/JuceModel.h"
#include "rec/slow/Components.h"
#include "rec/slow/GuiSettings.pb.h"
#include "rec/slow/Instance.h"
#include "rec/slow/MainPage.h"
#include "rec/slow/SlowWindow.h"
#include "rec/slow/commands/Command.pb.h"
#include "rec/gui/GetTooltip.h"
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

const int MS_TILL_TOOLTIP = 700;

}  // namespace

GuiListener::GuiListener()
    : displayHelpPane_(false), lastComponent_(nullptr), lastFocus_(nullptr) {
}

void GuiListener::operator()(const GuiSettings& settings) {
  if (!settings.show_tooltips()) {
    tooltipWindow_.reset();

  } else if (!tooltipWindow_) {
    tooltipWindow_.reset(new TooltipWindow(nullptr, MS_TILL_TOOLTIP));
  }

  Lock l(lock_);
  displayHelpPane_ = settings.show_help_pane();
}

void GuiListener::operator()(TransportCommand command) {
  if (command == TOGGLE_START_STOP)
    invokeAndCheck(Command::TOGGLE_START_STOP);

  else if (command == JUMP_TO_FIRST)
    invokeAndCheck(Command::JUMP + CommandIDs::FIRST);

  else if (command == JUMP_TO_PREVIOUS)
    invokeAndCheck(Command::JUMP + CommandIDs::PREVIOUS);

  else if (command == JUMP_TO_NEXT)
    invokeAndCheck(Command::JUMP + CommandIDs::NEXT);
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

  Component* comp = gui::getComponentUnderMouse();

  if (comp != lastComponent_) {
    lastComponent_ = comp;
    getInstance()->components_->mainPage_->setTooltip(gui::getTooltip(comp));
  }

#if JUCE_DEBUG
  comp = Component::getCurrentlyFocusedComponent();
  if (comp != lastFocus_) {
    // DLOG(INFO) << (comp ? str(comp->getName()) : string("(none)"));
    lastFocus_ = comp;
  }
#endif
}

}  // namespace slow
}  // namespace rec
