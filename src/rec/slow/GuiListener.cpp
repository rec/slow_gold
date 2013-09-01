#include "rec/slow/GuiListener.h"

#include "rec/gui/GuiWriteable.h"
#include "rec/slow/Components.h"
#include "rec/slow/GuiSettings.pb.h"
#include "rec/slow/MainPage.h"
#include "rec/slow/SlowWindow.h"
#include "rec/slow/commands/SlowCommand.pb.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {
namespace slow {

using namespace juce;
using namespace rec::command;
using namespace rec::gui::audio;

static const int MS_TILL_TOOLTIP = 700;

GuiListener::GuiListener(Instance* i)
    : HasInstance(i), displayHelpPane_(false), lastComponent_(nullptr),
      lastFocus_(nullptr) {
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
    broadcast(SlowCommand::TOGGLE_START_STOP);

  else if (command == JUMP_TO_FIRST)
    broadcast(ID(SlowCommand::JUMP, ID::FIRST));

  else if (command == JUMP_TO_PREVIOUS)
    broadcast(ID(SlowCommand::JUMP, ID::PREVIOUS));

  else if (command == JUMP_TO_NEXT)
    broadcast(ID(SlowCommand::JUMP, ID::NEXT));
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
    components()->mainPage_->setTooltip(getTooltip(comp));
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
