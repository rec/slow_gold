#include "rec/slow/Menus.h"

#include "rec/base/ArraySize.h"
#include "rec/command/CommandIDEncoder.h"
#include "rec/slow/GuiSettings.pb.h"
#include "rec/slow/Instance.h"
#include "rec/slow/MenuMaker.h"
#include "rec/slow/Target.h"

using namespace rec::command;

namespace rec {
namespace slow {

Menus::Menus(Instance* i) : HasInstance(i) {}

void Menus::operator()(const GuiSettings& settings) {
  setMenuMaker(settings.advanced_menus());
}

void Menus::setMenuMaker(bool isAdvanced) {
  Lock l(lock_);
  menuMaker_.reset(new MenuMaker(target()->targetManager()));
}

const StringArray Menus::getMenuBarNames() {
  static const char* NAMES[] = {"File", "Edit", "Audio", "Transport", "Select",
                                "Display"};
  return StringArray(NAMES, arraysize(NAMES));
}

const PopupMenu Menus::getMenuForIndex(int menuIndex, const String& menuName) {
  if (!menuMaker_)
    setMenuMaker(false);
  return menuMaker_->makeMenu(menuName);
}

}  // namespace slow
}  // namespace rec

