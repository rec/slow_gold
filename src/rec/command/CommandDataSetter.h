#ifndef __REC_COMMAND_COMMANDDATASETTER__
#define __REC_COMMAND_COMMANDDATASETTER__

#include "rec/command/Command.h"
#include "rec/util/thread/Callback.h"
#include "rec/util/DataListener.h"

namespace rec {
namespace command {

template <typename Proto>
class CommandDataSetter : public DataListener<Proto>, public CommandItemSetter {
 public:
  explicit CommandDataSetter(Listener<None>* changeListener,
                             const Command& command,
                             const data::Address& addr =
                             data::Address::default_instance(),
                             bool isGlobal = false)
      : DataListener<Proto>(addr, isGlobal),
        changeListener_(changeListener),
        command_(command) {
  }

  virtual ~CommandDataSetter() {
    DLOG(INFO) << "Deleting " << this;
  }

  virtual void onDataChange(const Proto& p) {
    data::Value value = this->getValue();
    int index = value.get<bool>() ? 1 : 0;
    if (index < command_.desc().menu_size())
      menuName_ = command_.desc().menu(index);
    else
      LOG(ERROR) << "No " << index << " in " << command_.ShortDebugString();
    (*changeListener_)(None());
  }

  virtual void execute() {
    data::Value value = this->getValue();
    value.set_bool_f(value.bool_f());
    this->setValue(value);
  }

  virtual string menuName() const { Lock l(lock_); return menuName_; }

 private:
  CriticalSection lock_;
  Listener<None>* changeListener_;

  const Command command_;
  string menuName_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(CommandDataSetter);
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMANDDATASETTER__
