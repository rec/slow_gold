#ifndef __REC_COMMAND_COMMANDDATASETTER__
#define __REC_COMMAND_COMMANDDATASETTER__

#include "rec/command/Command.h"
#include "rec/util/thread/Callback.h"

namespace rec {
namespace command {

template <typename Proto>
class CommandDataSetter : public DataListener<Proto>, public Callback {
 public:
  explicit CommandDataSetter(const Command& command,
                             const data::Address& addr =
                             data::Address::default_instance(),
                             bool isGlobal = false)
      : DataListener<Proto>(addr, isGlobal), command_(command) {
  }

  virtual void onDataChange(const Proto& p) {
    data::Value value = getValue();
    int index = value.get<bool>() ? 1 : 0;
    if (index < command_.desc().menu_size())
      menuName_ = command_.desc().menu(index);
    else
      LOG(ERROR) << "No " << index << " in " << command_.ShortDebugString();
  }

  virtual void operator()() {
    data::Value value = getValue();
    value.set_bool_f(value.bool_f());
    setValue(value);
  }

  virtual string menuName() const { Lock l(lock_); return menuName_; }

 private:
  CriticalSection lock_;

  const Command& command_;
  string menuName_;

  DISALLOW_COPY_AND_ASSIGN(CommandDataSetter);
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMANDDATASETTER__
