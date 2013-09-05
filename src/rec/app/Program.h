#ifndef __REC_APP_PROGRAM__
#define __REC_APP_PROGRAM__

#include <unordered_map>

#include "rec/app/Menu.pb.h"
#include "rec/command/Command.pb.h"
#include "rec/gui/menu/RecentFiles.h"
#include "rec/util/thread/Callback.h"

namespace rec {
namespace app {

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

class ProgramBase : public Program {
 public:
  ProgramBase() {}

  void addCallback(CommandID command, unique_ptr<Callback> callback) override {
    auto loc = commandMap_.find(command);
    if (loc == commandMap_.end())
      commandMap_.insert(loc, std::make_pair(command, std::move(callback)));
    else
      LOG(DFATAL) << "Duplicate command ID " << command;
  }

  Callback* getCallback(CommandID command) const override {
    Callback* callback = nullptr;
    auto loc = commandMap_.find(command);
    if (loc != commandMap_.end())
      callback = loc->second.get();
    LOG_IF(DFATAL, not callback) << "No callback for " << command;
    return callback;
  }

 private:
  typedef std::unordered_map<CommandID, unique_ptr<Callback>> CommandMap;
  CommandMap commandMap_;
};

template <typename PARTS>
bool hasProperty(const Program& program, const PARTS& parts) {
  for (auto& part: parts) {
    if (program.hasProperty(part))
      return true;
  }
  return false;
}

}  // namespace app
}  // namespace rec


#endif  // __REC_APP_PROGRAM__
