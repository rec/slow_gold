#include "rec/util/Disableable.h"

namespace rec {
namespace util {

void Disableable::setDisableProperty(const string& name, bool value) {
  Lock l(lock_);
  propertyMap_[name] = value;
}

bool Disableable::getDisabledFromProperties() const {
  Lock l(lock_);
  for (auto& i: propertyMap_) {
    if (i.second)
      return true;
  }
  return false;
}

void Disableable::disable(bool isDisabled) {
  if (Component* c = dynamic_cast<Component*>(this)) {
    DLOG(INFO) << (isDisabled ? "disabling " : "enabling ") << str(c->getName());
    DCHECK(c->getName().length());
    c->setEnabled(not isDisabled);
  } else
    LOG(DFATAL) << "A Disableable wasn't a Component.";
}


}  // namespace util
}  // namespace rec

