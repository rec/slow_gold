#pragma once

#include "rec/base/base.h"

namespace rec {

namespace program { class Program; }

namespace slow {

void addGlobalCallbacks(program::Program* t);
void requestSupport();

}  // namespace slow
}  // namespace rec

