#include "rec/command/CommandDataSetter.h"

namespace rec {
namespace command {

CommandDataSetter::CommandDataSetter(Listener<None>* changeListener,
                                     const Command& command,
                                     const data::Address& addr,
                                     bool isGlobal)
    : UntypedDataListener(command.setter_type_name(), addr, isGlobal),
      changeListener_(changeListener),
      command_(command),
      menuName_("none") {
}

void CommandDataSetter::operator()(const Message& m) {
  data::Value value = getValue();
  int index = value.get<bool>() ? 1 : 0;
  if (index < command_.desc().menu_size())
    menuName_ = command_.desc().menu(index);
  else
    LOG(DFATAL) << "No " << index << " in " << command_.ShortDebugString();

  (*changeListener_)(None());
}

void CommandDataSetter::execute() {
  data::Value value = this->getValue();
  value.set_bool_f(!value.bool_f());
  setValue(value);
}

string CommandDataSetter::menuName() const {
  Lock l(lock_);
  return menuName_;
}

}  // namespace command
}  // namespace rec
