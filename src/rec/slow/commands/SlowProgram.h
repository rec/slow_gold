#ifndef __REC_SLOW_COMMANDS_SLOWPROGRAM__
#define __REC_SLOW_COMMANDS_SLOWPROGRAM__

#include "rec/app/Program.h"
#include "rec/gui/menu/RecentFiles.h"

namespace rec {
namespace slow {

class SlowProgram : public app::ProgramBase {
 public:
  SlowProgram() {}

  command::Commands commands() const override;
  command::Commands keypresses() const override;
  app::Menus menus() const override;
  app::MenuCollection menuCollection() const override;
  string menuBarName() const override;

  bool hasProperty(const string& name) const override;
  string makeMenuName(const command::Command&, CommandID) const override;

  // Add an entry only for MenuEntries which have a callout_function.
  void addMenuEntry(PopupMenu*, const app::MenuEntry&) const override {}

  const gui::RecentFilesStrategy& recentFilesStrategy() const override;

  void registerAllCallbacks() override;

 private:
  DISALLOW_COPY_ASSIGN_AND_LEAKS(SlowProgram);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_COMMANDS_SLOWPROGRAM__
