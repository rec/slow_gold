#ifndef __REC_COMMAND_TICKEDDATASETTER__
#define __REC_COMMAND_TICKEDDATASETTER__

#include "rec/command/CommandDataSetter.h"

namespace rec {
namespace command {

class TickedDataSetter : public CommandDataSetter {
 public:
  TickedDataSetter(ApplicationCommandInfo* info,
                   Listener<None>* changeListener,
                   const Command& command,
                   const data::Address& a,
                   bool isGlobal);

  virtual ~TickedDataSetter() {}

  virtual void operator()(const Message&);
  virtual void execute();
  virtual string menuName() const;

 private:
  ApplicationCommandInfo* info_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(TickedDataSetter);
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_TICKEDDATASETTER__
