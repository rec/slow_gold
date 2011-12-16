#include "rec/command/TickedDataSetter.h"

namespace rec {
namespace command {

TickedDataSetter::TickedDataSetter(ApplicationCommandInfo* info,
                                   Listener<None>* changeListener,
                                   const Command& command,
                                   const data::Address& addr,
                                   bool isGlobal)
    : CommandDataSetter(changeListener, command, addr, isGlobal),
      info_(info) {
}

void TickedDataSetter::operator()(const Message&) {
  data::Value v = getValue();
  info_->setTicked(v.get<bool>());

  (*changeListener_)(None());
}

void TickedDataSetter::execute() {
  data::Value value = this->getValue();
  value.set_bool_f(!value.bool_f());
  this->setValue(value);
}

string TickedDataSetter::menuName() const {
  Lock l(lock_);
  return command_.desc().menu(0);
}

}  // namespace command
}  // namespace rec
