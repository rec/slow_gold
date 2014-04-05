#include "rec/gui/GetComponentMap.h"

namespace rec {
namespace gui {

namespace {

void getComponentMap(Component* comp, ComponentMap* map) {
  auto parent = comp->getParentComponent();
  DCHECK(parent);
  string name = str(comp->getName());
  if (not name.empty()) {
    ComponentKey key(name, parent);
    try {
      map->at(key);
      LOG(ERROR) << "Duplicate component name " << name;
    } catch (std::out_of_range&) {
      (*map)[key] = comp;
    }
  } else {
    LOG(ERROR) << "Empty component name.";
  }

  for (int i = 0; i < comp->getNumChildComponents(); ++i)
    getComponentMap(comp->getChildComponent(i), map);
}

}  // namespace

ComponentMap getComponentMap(Component* comp) {
  ComponentMap map;
  getComponentMap(comp, &map);
  return map;
}

}  // namespace gui
}  // namespace rec
