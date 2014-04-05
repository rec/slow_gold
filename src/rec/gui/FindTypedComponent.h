#pragma once

#include "rec/base/base.h"

namespace rec {
namespace gui {

Component* getRoot(Component*);
Component* findComponent(Component* root, const String& name);

template <typename Type>
Type* findTypedComponent(Component* root, const String& name) {
  if (Type* t = dynamic_cast<Type*>(findComponent(root, name)))
    return t;

  LOG(DFATAL) << name << " had wrong type.";
  return nullptr;
}

}  // namespace gui
}  // namespace rec
