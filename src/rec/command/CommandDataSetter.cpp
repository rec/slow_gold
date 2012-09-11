#include "rec/command/CommandDataSetter.h"
#include "rec/base/Trans.h"

namespace rec {
namespace command {

CommandDataSetter::CommandDataSetter(Listener<None>* changeListener,
                                     const Command& command,
                                     const data::Address& addr,
                                     Scope scope)
    : AddressListener(addr, command.setter().type_name(), scope),
      changeListener_(changeListener),
      command_(command),
      menuName_("none") {
}

void CommandDataSetter::operator()(const data::Value& value) {
  int index = value.get<bool>() ? 1 : 0;
  if (index < command_.desc().menu_size())
    menuName_ = command_.desc().menu(index);
  else
    LOG(DFATAL) << "No " << index << " in " << command_.ShortDebugString();

  (*changeListener_)(None());
}

void CommandDataSetter::execute() {
  data::Value value = getValue();
  value.set_bool_f(!value.bool_f());
  setValue(value);
}

string CommandDataSetter::menuName() const {
  Lock l(lock_);
  String s = Trans(menuName_);
  return str(s);
}

}  // namespace command
}  // namespace rec
