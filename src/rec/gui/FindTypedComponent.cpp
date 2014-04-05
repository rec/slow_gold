#include "rec/gui/FindTypedComponent.h"

namespace rec {
namespace gui {

Component* getRoot(Component* base) {
  auto child = base;
  while (base) {
    child = base;
    base = base->getParentComponent();
  }
  return child;
}

Component* findComponent(Component* root, const String& name) {
  auto result = (root->getName() == name) ? root : nullptr;
  for (auto i = 0; i < root->getNumChildComponents(); ++i) {
    auto child = root->getChildComponent(i);
    if (auto r = findComponent(child, name)) {
      LOG_IF(DFATAL, result) << "Two components for name " << name;
      result = r;
    }
  }

  return result;
}

}  // namespace gui
}  // namespace rec
