#ifndef __REC_SLOW_COMMANDS_SLOWPROGRAM__
#define __REC_SLOW_COMMANDS_SLOWPROGRAM__

#include "rec/program/ProgramBase.h"
#include "rec/gui/menu/RecentFiles.h"

namespace rec {
namespace slow {

class Instance;

class SlowProgram : public program::ProgramBase {
 public:
  explicit SlowProgram(Instance*);

  command::Commands commands() const override;
  command::KeyStrokeCommandMapProto keypresses() const override;
  program::Menus menus() const override;
  program::MenuCollection menuCollection() const override;
  string menuBarName() const override;

  bool hasProperty(const string& name) const override;
  void commandCallout(const command::Command&, ApplicationCommandInfo*)
    const override;

  // Add an entry only for MenuEntries which have a callout_function.
  void menuCallout(PopupMenu*, const program::MenuEntry&) const override {}

  const gui::RecentFilesStrategy& recentFilesStrategy() const override;

  VirtualFile getCurrentFile() const override;
  void beforeCommand(CommandID id) override;

  void registerAllCallbacks() override;
  string commandName(CommandID) const override;

 private:
  Instance* const instance_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(SlowProgram);
};

string commandName(CommandID);

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_COMMANDS_SLOWPROGRAM__
