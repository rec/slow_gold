#ifndef __REC_COMMAND_TICKEDDATASETTER__
#define __REC_COMMAND_TICKEDDATASETTER__

#include "rec/command/Command.h"
#include "rec/command/CommandItemSetter.h"
#include "rec/util/thread/Callback.h"
#include "rec/util/DataListener.h"

namespace rec {
namespace command {

class TickedDataSetter : public UntypedDataListener, public CommandItemSetter {
 public:
  TickedDataSetter(Listener<None>* changeListener,
                   const Command& command,
                   const data::Address& a = data::Address::default_instance(),
                   bool isGlobal = false)
      : UntypedDataListener(a, isGlobal), changeListener_(changeListener_)


 private:
  DISALLOW_COPY_ASSIGN_AND_LEAKS(TickedDataSetter);
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_TICKEDDATASETTER__
