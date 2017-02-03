#pragma once

#include "rec/base/base.h"

namespace rec {
namespace util {
namespace thread {

enum Result {
    CONTINUE = -4,
    YIELD = -3,
    DONE = -2,
    WAIT = -1  // Everything from -1 on is a wait.
};

}  // namespace thread
}  // namespace util
}  // namespace rec
