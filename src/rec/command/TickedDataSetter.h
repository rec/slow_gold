#ifndef __REC_COMMAND_TICKEDDATASETTER__
#define __REC_COMMAND_TICKEDDATASETTER__

#include "rec/command/CommandDataSetter.h"

namespace rec {
namespace command {

template <typename Proto>
class TickedDataSetter : public CommandDataSetter<Proto> {
 public:
  TickedDataSetter(ApplicationCommandInfo* info,
                   Listener<None>* changeListener,
                   const Command& command,
                   const data::Address& a = data::Address::default_instance(),
                   bool isGlobal = false)
      : CommandDataSetter<Proto>(changeListener, command, a, isGlobal),
        info_(info) {
  }

  virtual void onDataChange(const Proto& p) {
    data::Value v = this->getValue(); 
    info_->setTicked(v.get<bool>());

    (*this->changeListener_)(None());
  }

  virtual void execute() {
    data::Value value = this->getValue();
    value.set_bool_f(!value.bool_f());
    this->setValue(value);
  }

  virtual string menuName() const { Lock l(this->lock_); return this->command_.desc().menu(0); }

 private:
  ApplicationCommandInfo* info_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(TickedDataSetter);
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_TICKEDDATASETTER__
