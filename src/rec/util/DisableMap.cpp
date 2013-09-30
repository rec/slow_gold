#include "rec/util/DisableMap.h"

namespace rec {
namespace util {

void DisableMap::addComponent(Disableable* comp) {
  Lock l(lock_);
  components_.insert(comp);
  for (auto& i: comp->map()) {
    auto& name = i.first;
    componentMap_.insert({{name, comp}});
    if (not propertyMap_.count(name))
      propertyMap_[name] = false;
  }
}

bool DisableMap::getProperty(const string& name) const {
  try {
    return propertyMap_.at(name);
  } catch (const std::out_of_range&) {
    return false;
  }
}

bool DisableMap::setProperty(const string& name, bool value) {
  Lock l(lock_);
  auto& oldValue = propertyMap_[name];
  if (value == oldValue)
    return false;

  oldValue = value;
  auto r = componentMap_.equal_range(name);
  for (auto i = r.first; i != r.second; ++i) {
    auto& comp = i->second;
    comp->setDisableProperty(name, value);
    if (not disabled_)
      disable(comp, comp->getDisabledFromProperties());
  }
  return true;
}

bool DisableMap::setDisabled(bool isDisabled) {
  Lock l(lock_);
  if (isDisabled == disabled_)
    return false;
  disabled_ = isDisabled;
  for (auto& comp: components_)
    disable(comp, disabled_ or comp->getDisabledFromProperties());
  return true;
}

void DisableMap::disable(Disableable* comp, bool isDisabled) {
  if (Component* c = dynamic_cast<Component*>(comp))
    c->setEnabled(not isDisabled);
  else
    LOG(DFATAL) << "A Disableable wasn't a Component.";
}

}  // namespace util
}  // namespace rec
