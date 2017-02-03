#pragma once

#include "rec/base/base.h"

namespace rec {
namespace gui {

class ComponentProto;
class Constants;
class Context;

unique_ptr<Component> makeCustom(const Context&);

}  // namespace gui
}  // namespace rec

