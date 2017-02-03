#pragma once

#include "rec/base/base.h"

namespace rec {
namespace gui {

class Context;

unique_ptr<Component> makeButton(const Context&);

}  // namespace gui
}  // namespace rec

