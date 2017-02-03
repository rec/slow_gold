#pragma once

#include "rec/base/base.h"

namespace rec {
namespace gui {

template <typename Out>
void dump(Out& out, const Component& comp, const string& prefix = "") {
    auto& bounds = comp.getBounds();
    out << prefix
            << &comp << ": "
            << comp.getName()
            << (comp.isVisible() ? " " : " (NOT visible)")
            << ": (" << bounds.getX()
            << ", " << bounds.getY()
            << "), (" << bounds.getWidth()
            << ", " << bounds.getHeight()
            << ")\n";
}

template <typename Out>
void dumpRecursive(Out& out, const Component& comp, const string& prefix = "") {
    if (prefix.empty())
        out << "\n";
    dump(out, comp, prefix);
    auto p = prefix + "  ";
    for (auto i = 0; i < comp.getNumChildComponents(); ++i)
        dumpRecursive(out, *comp.getChildComponent(i), p);
}

}  // namespace gui
}  // namespace rec
