#include "rec/gui/DisableMap.h"

namespace rec {
namespace gui {


void DisableMap::addComponent(DisableableComponent* comp) {
  Lock l(lock_);
  components_.insert(comp);
  for (auto& i: comp->map()) {
    auto& name = i.first;
    componentMap_.insert({{name, comp}});
    if (not propertyMap_.count(name))
      propertyMap_[name] = false;
  }
}

void DisableMap::setProperty(const string& name, bool value) {
  Lock l(lock_);
  auto& oldValue = propertyMap_[name];
  if (value != oldValue) {
    oldValue = value;
    auto r = componentMap_.equal_range(name);
    for (auto i = r.first; i != r.second; ++i) {
      auto& comp = i->second;
      comp->setDisableProperty(name, value);
      if (not disabled_)
        disable(comp, comp->getDisabledFromProperties());
    }
  }
}

void DisableMap::setDisabled(bool isDisabled) {
  Lock l(lock_);
  if (isDisabled == disabled_)
    return;
  disabled_ = isDisabled;
  for (auto& comp: components_)
    disable(comp, disabled_ or comp->getDisabledFromProperties());
}

void DisableMap::disable(DisableableComponent* comp, bool isDisabled) {
  if (Component* c = dynamic_cast<Component*>(comp))
    c->setEnabled(not isDisabled);
  else
    LOG(DFATAL) << "A DisableableComponent wasn't a Component.";
}

}  // namespace gui
}  // namespace rec

