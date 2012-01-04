#include "rec/slow/Menus.h"

#include "rec/base/ArraySize.h"
#include "rec/command/CommandIDEncoder.h"
#include "rec/gui/RecentFiles.h"
#include "rec/slow/GuiSettings.pb.h"
#include "rec/slow/Instance.h"
#include "rec/slow/MenuMaker.h"
#include "rec/slow/Target.h"
#include "rec/util/Cuttable.h"
#include "rec/util/Undo.h"

using namespace rec::command;

namespace rec {
namespace slow {

static const int SLOT_COUNT = 10;

Menus::Menus(Instance* i) : HasInstance(i), isAdvanced_(false) {}

void Menus::operator()(const GuiSettings& settings) {
  //  isAdvanced_ = settings.advanced_menus();
}

const StringArray Menus::getMenuBarNames() {
  static const char* NAMES[] = {"File", "Edit", "Audio", "Transport", "Select",
                                "Display"};
  return StringArray(NAMES, arraysize(NAMES));
}

const PopupMenu Menus::getMenuForIndex(int menuIndex, const String& menuName) {
  return MenuMaker(target()->targetManager()).makeMenu(menuName);
}

}  // namespace slow
}  // namespace rec

