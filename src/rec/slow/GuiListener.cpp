#include "rec/slow/GuiListener.h"

#include "rec/gui/GetHelpText.h"
#include "rec/gui/GuiWriteable.h"
#include "rec/program/JuceModel.h"
#include "rec/slow/GuiSettings.pb.h"
#include "rec/slow/SlowWindow.h"
#include "rec/slow/commands/Command.pb.h"
#include "rec/util/Cuttable.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/util/DisableMap.h"

namespace rec {
namespace slow {

const int MS_TILL_TOOLTIP = 350;

GuiListener::GuiListener()
    : displayHelpPane_(false), lastComponent_(nullptr) {
}

void GuiListener::operator()(const GuiSettings& settings) {
  if (!settings.show_tooltips())
    tooltipWindow_.reset();
  else if (!tooltipWindow_)
    tooltipWindow_.reset(new juce::TooltipWindow(nullptr, MS_TILL_TOOLTIP));

  Lock l(lock_);
  displayHelpPane_ = settings.show_help_pane();
}

void GuiListener::update() {
  gui::GuiWriteable::writeAll();
  {
    Lock l(lock_);
    if (!displayHelpPane_)
      return;
  }
  gui::refreshHelpText();

  Component* c = Component::getCurrentlyFocusedComponent();
  if (lastComponent_ != c) {
    lastComponent_ = c;
    auto dm = program::juceModel()->disableMap();
    bool b1 = dm->setProperty("cant_copy", not canCopy());
    bool b2 = dm->setProperty("cant_cut", not canCut());
    bool b3 = dm->setProperty("cant_paste", not canPaste());
    if (b1 or b2 or b3)
      program::menuItemsChanged();
  }
}

}  // namespace slow
}  // namespace rec
