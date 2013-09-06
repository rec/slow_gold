#ifndef __REC_PROGRAM_PROGRAMBASE__
#define __REC_PROGRAM_PROGRAMBASE__

#include <unordered_map>

#include "rec/Program/Program.h"

namespace rec {
namespace program {

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

}  // namespace program
}  // namespace rec

#endif  // __REC_PROGRAM_PROGRAMBASE__
