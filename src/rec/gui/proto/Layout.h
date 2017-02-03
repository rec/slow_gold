#pragma once

#include "rec/base/base.h"

namespace rec {
namespace gui {

class Context;

std::unique_ptr<Component> makeLayout(const string& name, Component* parent);
std::unique_ptr<Component> makeLayoutComp(const Context&);

}  // namespace gui
}  // namespace rec
