#pragma once

#include "rec/base/base.h"

namespace rec {
namespace gui {

class Context;

std::unique_ptr<Component> makeLevelMeter(const Context&);

}  // namespace gui
}  // namespace rec
