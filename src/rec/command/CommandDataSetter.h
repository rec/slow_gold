#ifndef __REC_COMMAND_COMMANDDATASETTER__
#define __REC_COMMAND_COMMANDDATASETTER__

#include "rec/command/CommandRecord.h"
#include "rec/util/thread/Callback.h"
#include "rec/data/Address.h"
#include "rec/data/AddressListener.h"
#include "rec/data/Value.h"

namespace rec {
namespace command {

class CommandDataSetter : public data::AddressListener,
                          public CommandItemSetter {
 public:
  explicit CommandDataSetter(MenuBarModel* changeListener,
                             const Command& command,
                             const data::Address& addr,
                             Scope scope);
  virtual ~CommandDataSetter() {}

  virtual void operator()(const data::Value&);
  virtual void execute();
  virtual string menuName() const;

 protected:
  CriticalSection lock_;

  MenuBarModel* changeListener_;
  const Command& command_;
  string menuName_;

 private:
  DISALLOW_COPY_ASSIGN_AND_LEAKS(CommandDataSetter);
};


}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMANDDATASETTER__
