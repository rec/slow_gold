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
                          PopupMenu* m,
                          int flags) {
  add(CommandIDEncoder::toCommandID(slot, command), name, true, m, flags);
}

void MenuMaker::addSimpleRepeat(Command::Type command, int slot, PopupMenu* m) {
  add(CommandIDEncoder::toCommandID(slot, command), "", !empty_, m, 0);
}

void MenuMaker::addEnabled(Command::Type command, bool enabled) {
  add(command, "", enabled);
}

void MenuMaker::addIfNotEmpty(Command::Type command) {
  addEnabled(command, !empty_);
}

void MenuMaker::addBank(Command::Type command, const String& name) {
  PopupMenu sub;
  for (int i = command::CommandIDEncoder::FIRST; i < SLOT_COUNT; ++i) {
    if (i == 0)
      sub.addSeparator();
    addSimpleRepeat(command, i, &sub);
  }

  menu_.addSubMenu(name, sub, !empty_);
}

MenuMaker* makeMenuMaker(command::TargetManager* tm, bool isAdvanced,
                         const IsWholeSong& isWholeSong, bool empty) {
  if (isAdvanced)
    return new AdvancedMenuMaker(tm, isWholeSong, empty);
  else
    return new BasicMenuMaker(tm, isWholeSong, empty);
}

}  // namespace slow
}  // namespace rec
