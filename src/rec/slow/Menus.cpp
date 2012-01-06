#include "rec/slow/Menus.h"

#include "rec/slow/GuiSettings.pb.h"
#include "rec/slow/MenuMaker.h"
#include "rec/slow/Target.h"

using namespace rec::command;

namespace rec {
namespace slow {

Menus::Menus(Instance* i) : HasInstance(i), advanced_(false) {}
Menus::~Menus() {}

void Menus::operator()(const GuiSettings& settings) {
  Lock l(lock_);
  advanced_ = settings.advanced_menus();
}

MenuMaker* Menus::getMenuMaker() {
  Lock l(lock_);
  return makeMenuMaker(target()->targetManager(), advanced_);
}

const StringArray Menus::getMenuBarNames() {
  return ptr<MenuMaker>(getMenuMaker())->getMenuBarNames();
}

const PopupMenu Menus::getMenuForIndex(int menuIndex, const String& menuName) {
  return ptr<MenuMaker>(getMenuMaker())->makeMenu(menuName);
}

}  // namespace slow
}  // namespace rec

