#ifndef __REC_APP_PROGRAM__
#define __REC_APP_PROGRAM__

#include "rec/program/Menu.pb.h"
#include "rec/command/Command.pb.h"
#include "rec/gui/menu/RecentFiles.h"
#include "rec/util/thread/Callback.h"

namespace rec {
namespace program {

class Program {
 public:
  Program() {}
  virtual ~Program() {}

  virtual command::Commands commands() const = 0;
  virtual command::Commands keypresses() const = 0;
  virtual Menus menus() const = 0;
  virtual MenuCollection menuCollection() const = 0;
  virtual string menuBarName() const = 0;

  virtual bool hasProperty(const string& name) const = 0;
  virtual string makeMenuName(const command::Command&, CommandID) const = 0;

  // Add an entry only for MenuEntries which have a callout_function.
  virtual void addMenuEntry(PopupMenu*, const MenuEntry&) const = 0;

  virtual const gui::RecentFilesStrategy& recentFilesStrategy() const = 0;

  virtual void registerAllCallbacks() = 0;
  virtual void addCallback(CommandID, unique_ptr<Callback>) = 0;
  virtual Callback* getCallback(CommandID) const = 0;
};

template <typename PARTS>
bool hasProperty(const Program& program, const PARTS& parts) {
  for (auto& part: parts) {
    if (program.hasProperty(part))
      return true;
  }
  return false;
}

}  // namespace program
}  // namespace rec

#endif  // __REC_APP_PROGRAM__
