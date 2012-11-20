#include "rec/slow/MenuMaker.h"

#include "rec/base/ArraySize.h"
#include "rec/command/CommandIDEncoder.h"
#include "rec/command/CommandRecordTable.h"
#include "rec/gui/RecentFiles.h"
#include "rec/slow/AdvancedMenuMaker.h"
#include "rec/slow/BasicMenuMaker.h"
#include "rec/slow/Instance.h"
#include "rec/slow/Target.h"
#include "rec/util/Cuttable.h"
#include "rec/util/Undo.h"
#include "rec/widget/waveform/Viewport.pb.h"

namespace rec {
namespace slow {

using namespace rec::command;
using widget::waveform::Viewport;

const PopupMenu MenuMaker::makeMenu(const String& name) {
  Lock l(lock_);

  menu_.clear();
  addMenu(name);
  return menu_;
}

void MenuMaker::addFull(CommandID id,
                        const String& name,
                        Enable enable,
                        PopupMenu* m,
                        int flags) {
  commandRecordTable()->fillCommandInfo(id, name, flags, enable);
  (m ? m : &menu_)->addCommandItem(applicationCommandManager(), id);
}


void MenuMaker::addBasic(CommandID id) {
  addFull(id, String::empty, ENABLE, NULL, -1);
}

void MenuMaker::addRepeat(Command::Type command,
                          int slot,
                          const String& name,
                          PopupMenu* m,
                          int flags) {
  addFull(CommandIDEncoder::toCommandID(slot, command), name, ENABLE, m, flags);
}

void MenuMaker::addSimpleRepeat(Command::Type command, int slot, PopupMenu* m) {
  addFull(CommandIDEncoder::toCommandID(slot, command), "",
          empty_ ? DISABLE : ENABLE, m, DEFAULT_FLAGS);  // Was 0!!
}

void MenuMaker::addEnabled(Command::Type command, Enable enable) {
  addEnabledName(command, enable, String::empty);
}

void MenuMaker::addEnabledName(Command::Type cmd, Enable enable,
                               const String& name) {
  addFull(cmd, name, enable, NULL, DEFAULT_FLAGS);
}

void MenuMaker::addBank(Command::Type command, const String& name) {
  int lastSlot = SLOT_COUNT;

  if (!Instance::getInstance()->empty()) {
    lastSlot = std::min(data::getProto<Viewport>(Instance::getInstanceFile()).
                   loop_points().loop_point_size(), lastSlot);
  }

  PopupMenu sub;
  for (int i = command::CommandIDEncoder::FIRST; i < lastSlot; ++i) {
    if (i == 0)
      sub.addSeparator();
    addSimpleRepeat(command, i, &sub);
  }

  menu_.addSubMenu(name, sub, !empty_);
}

MenuMaker* makeMenuMaker(slow::Instance* instance, bool isAdvanced,
                         const IsWholeSong& isWholeSong, bool empty) {
  if (isAdvanced)
    return new AdvancedMenuMaker(instance, isWholeSong, empty);
  else
    return new BasicMenuMaker(instance, isWholeSong, empty);
}

}  // namespace slow
}  // namespace rec
