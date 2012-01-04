#include "rec/slow/Menus.h"

#include "rec/slow/GuiSettings.pb.h"
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
  menuMaker_.reset(makeMenuMaker(target()->targetManager(), isAdvanced));
}

MenuMaker* Menus::getMenuMaker() {
  if (!menuMaker_)
    setMenuMaker(false);
  return menuMaker_.get();
}

const StringArray Menus::getMenuBarNames() {
  return getMenuMaker()->getMenuBarNames();
}

const PopupMenu Menus::getMenuForIndex(int menuIndex, const String& menuName) {
  return getMenuMaker()->makeMenu(menuName);
}

}  // namespace slow
}  // namespace rec

