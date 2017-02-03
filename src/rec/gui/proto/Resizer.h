#pragma once

#include "rec/base/base.h"

namespace rec {
namespace gui {

class Context;

std::unique_ptr<Component> makeResizer(const Context&);
std::unique_ptr<Component> makeSimpleResizer(const Context&);

}  // namespace gui
}  // namespace rec
