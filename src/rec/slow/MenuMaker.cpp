#include "rec/slow/MenuMaker.h"

#include "rec/base/ArraySize.h"
#include "rec/command/CommandIDEncoder.h"
#include "rec/command/TargetManager.h"
#include "rec/gui/RecentFiles.h"
#include "rec/slow/AdvancedMenuMaker.h"
#include "rec/slow/BasicMenuMaker.h"
#include "rec/util/Cuttable.h"
#include "rec/util/Undo.h"

namespace rec {
namespace slow {

using namespace rec::command;

const PopupMenu MenuMaker::makeMenu(const String& name) {
  Lock l(lock_);
  menu_.clear();
  addMenu(name);
  return menu_;
}

void MenuMaker::add(CommandID id,
                    const String& name,
                    bool enabled,
                    PopupMenu* m,
                    int flags) {
  targetManager_->addCommandItem(m ? m : &menu_, id, enabled, name, flags);
}

void MenuMaker::addRepeat(Command::Type command,
                          int slot,
                          const String& name,
                          bool enabled,
                          PopupMenu* m,
                          int flags) {
  add(CommandIDEncoder::toCommandID(slot, command), name, enabled, m, flags);
}

void MenuMaker::addEnabled(Command::Type command, bool enabled) {
  add(command, "", enabled);
}

void MenuMaker::addBank(Command::Type command, const String& name, int begin,
                        int end) {
  Lock l(lock_);
  PopupMenu sub;
  for (int i = begin; i < end; ++i) {
    if (i == 0)
      sub.addSeparator();
    addRepeat(command, i, "", true, &sub);
  }

  menu_.addSubMenu(name, sub);
}

MenuMaker* makeMenuMaker(command::TargetManager* tm, bool isAdvanced,
                         const IsWholeSong& isWholeSong, bool isEmpty) {
  if (isAdvanced)
    return new AdvancedMenuMaker(tm, isWholeSong, isEmpty);
  else
    return new BasicMenuMaker(tm, isWholeSong, isEmpty);
}

}  // namespace slow
}  // namespace rec
