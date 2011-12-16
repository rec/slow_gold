#ifndef __REC_COMMAND_COMMANDDATASETTER__
#define __REC_COMMAND_COMMANDDATASETTER__

#include "rec/command/Command.h"
#include "rec/util/thread/Callback.h"
#include "rec/util/DataListener.h"
#include "rec/util/UntypedDataListener.h"

namespace rec {
namespace command {

class CommandDataSetter : public UntypedDataListener,
                                 public CommandItemSetter {
 public:
  explicit CommandDataSetter(Listener<None>* changeListener,
                             const Command& command,
                             const data::Address& addr =
                             data::Address::default_instance(),
                             bool isGlobal = false);
  virtual ~CommandDataSetter() {}

  virtual void operator()(const Message&);
  virtual void execute();
  virtual string menuName() const;

 protected:
  CriticalSection lock_;
  Listener<None>* changeListener_;

  const Command& command_;
  string menuName_;

 private:
  DISALLOW_COPY_ASSIGN_AND_LEAKS(CommandDataSetter);
};


}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMANDDATASETTER__
