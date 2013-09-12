#include "rec/slow/GuiListener.h"

#include "rec/gui/GuiWriteable.h"
#include "rec/program/JuceModel.h"
#include "rec/slow/Components.h"
#include "rec/slow/GuiSettings.pb.h"
#include "rec/slow/Instance.h"
#include "rec/slow/MainPage.h"
#include "rec/slow/SlowWindow.h"
#include "rec/slow/commands/SlowCommand.pb.h"
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
    invokeAndCheck(SlowCommand::TOGGLE_START_STOP);

  else if (command == JUMP_TO_FIRST)
    invokeAndCheck(SlowCommand::JUMP + CommandIDs::FIRST);

  else if (command == JUMP_TO_PREVIOUS)
    invokeAndCheck(SlowCommand::JUMP + CommandIDs::PREVIOUS);

  else if (command == JUMP_TO_NEXT)
    invokeAndCheck(SlowCommand::JUMP + CommandIDs::NEXT);
}

void GuiListener::operator()(CommandBarCommand command) {
  if (command == ADD_LOOP_POINT)
    invokeAndCheck(SlowCommand::ADD_LOOP_POINT);

  else if (command == ZOOM_OUT_FULL)
    invokeAndCheck(SlowCommand::ZOOM_OUT_FULL);

  else if (command == ZOOM_TO_SELECTION)
    invokeAndCheck(SlowCommand::ZOOM_TO_SELECTION);
}

static String getTooltip(Component* c) {
  while (c) {
    if (TooltipClient* ttc = dynamic_cast<TooltipClient*>(c)) {
      const String& s = ttc->getTooltip();
      if (s.length())
       return s;
    }
    c = c->getParentComponent();
  }
  return "";
}

void GuiListener::update() {
  gui::GuiWriteable::writeAll();
  {
    Lock l(lock_);
    if (!displayHelpPane_)
      return;
  }

  Component* comp = Desktop::getInstance().
    getMainMouseSource().getComponentUnderMouse();

  if (comp != lastComponent_) {
    lastComponent_ = comp;
    getInstance()->components_->mainPage_->setTooltip(getTooltip(comp));
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
