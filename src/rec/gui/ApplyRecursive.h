#pragma once

#include "rec/base/base.h"

namespace rec {
namespace gui {

template <typename Function>
void applyRecursiveDepthFirst(Function f, Component* c) {
    for (auto i = 0; i < c->getNumChildComponents(); ++i)
        f(c->getChildComponent(i));
    f(c);
}

template <typename Function>
void applyRecursiveBreadthFirst(Function f, Component* c) {
    f(c);
    for (auto i = 0; i < c->getNumChildComponents(); ++i)
        f(c->getChildComponent(i));
}

}  // namespace gui
}  // namespace rec
