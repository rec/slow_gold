#ifndef __REC_COMMAND_TICKEDDATASETTER__
#define __REC_COMMAND_TICKEDDATASETTER__

#include "rec/command/CommandDataSetter.h"

namespace rec {

namespace data { class Address; }
namespace data { class Value; }

namespace command {

class TickedDataSetter : public CommandDataSetter {
 public:
  TickedDataSetter(ApplicationCommandInfo* info,
                   MenuBarModel* changeListener,
                   const Command& command,
                   const data::Address& a,
                   Scope scope);
  virtual ~TickedDataSetter() {}

  virtual void operator()(const data::Value&);
  virtual void execute();
  virtual string menuName() const;

 private:
  ApplicationCommandInfo* const info_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(TickedDataSetter);
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_TICKEDDATASETTER__
