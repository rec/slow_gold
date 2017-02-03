#pragma once

#include "rec/base/base.h"

namespace rec {
namespace gui {

class ComponentProto;
class Constants;
class Context;

std::unique_ptr<Component> makeTimeDial(const Context&);

}  // namespace gui
}  // namespace rec
