#pragma once

#include "rec/base/base.h"

namespace rec {
namespace util {

template <typename Thread>
bool shouldExit(Thread* thread) {
    return thread && thread->threadShouldExit();
}

}  // namespace util
}  // namespace rec

