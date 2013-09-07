#ifndef __REC_SLOW_COMMANDS_SLOWPROGRAM__
#define __REC_SLOW_COMMANDS_SLOWPROGRAM__

#include "rec/command/map/CommandMap.pb.h"
#include "rec/program/ProgramBase.h"
#include "rec/gui/menu/RecentFiles.h"

namespace rec {
namespace slow {

class Instance;

class SlowProgram : public program::ProgramBase {
 public:
  explicit SlowProgram(Instance* instance) : instance_(instance) {}

  command::Commands commands() const override;
  command::KeyStrokeCommandMapProto keypresses() const override;
  program::Menus menus() const override;
  program::MenuCollection menuCollection() const override;
  string menuBarName() const override;

  bool hasProperty(const string& name) const override;
  string makeMenuName(const command::Command&, CommandID) const override;

  // Add an entry only for MenuEntries which have a callout_function.
  void addMenuEntry(PopupMenu*, const program::MenuEntry&) const override {}

  const gui::RecentFilesStrategy& recentFilesStrategy() const override;

  VirtualFile getCurrentFile() const override;

  void registerAllCallbacks() override;

 private:
  Instance* const instance_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(SlowProgram);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_COMMANDS_SLOWPROGRAM__
