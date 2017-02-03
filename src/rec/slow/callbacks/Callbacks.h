#pragma once

#include "rec/base/base.h"

namespace rec {

namespace program { class Program; }

namespace slow {

static const int REPEATED_COUNT = 10;

void addSlowCallbacks(program::Program*, int repeat = REPEATED_COUNT);

}  // namespace slow
}  // namespace rec

