#pragma once

#include "rec/base/base.h"

namespace rec {
namespace gui {

class Context;

unique_ptr<Component> makeResizer(const Context&);
unique_ptr<Component> makeSimpleResizer(const Context&);

}  // namespace gui
}  // namespace rec

