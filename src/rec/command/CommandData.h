#ifndef __REC_COMMAND_COMMANDDATA__
#define __REC_COMMAND_COMMANDDATA__

#include "rec/Command/Command.h"
#include "rec/util/Listener.h"

namespace rec {
namespace command {

class Access;

class CommandData {
 public:
  CommandData() {}
  virtual ~CommandData() {}

  virtual const Commands& commands() const = 0;
  virtual const Commands& repeated() const = 0;
  virtual const Commands& setters() const = 0;
  virtual const Commands& descriptions(const Access&) const = 0;
  virtual const Commands& keyPresses(const Access&) const = 0;
  virtual const Commands& allCommands() const = 0;

  virtual void addCallbacks(CommandRecordTable*) const = 0;
  virtual Listener<None>* getMenuUpdateListener() const = 0;
};
}
  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMANDDATA__
