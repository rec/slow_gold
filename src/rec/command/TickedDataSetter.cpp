#include "rec/command/TickedDataSetter.h"

namespace rec {
namespace command {

TickedDataSetter::TickedDataSetter(ApplicationCommandInfo* info,
                                   Listener<None>* changeListener,
                                   const Command& command,
                                   const data::Address& addr,
                                   Scope scope)
    : CommandDataSetter(changeListener, command, addr, scope),
      info_(info) {
}

void TickedDataSetter::operator()(const data::Value& v) {
  info_->setTicked(v.get<bool>());

  (*changeListener_)(None());
}

void TickedDataSetter::execute() {
  data::Value value = this->getValue();
  value.set_bool_f(!value.bool_f());
  setValue(value, CAN_UNDO);
}

string TickedDataSetter::menuName() const {
  Lock l(lock_);
  return command_.desc().menu(0);
}

}  // namespace command
}  // namespace rec
