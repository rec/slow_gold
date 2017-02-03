#pragma once

#include "rec/base/base.h"

namespace rec {

namespace program { class Program; }

namespace slow {

void addRepeatedCallbacks(program::Program*, int repeat);
void addSelectionCallbacks(program::Program*);

}  // namespace slow
}  // namespace rec
