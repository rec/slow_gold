#pragma once

#include "rec/util/range/Range.h"

namespace rec {
namespace util {

template <typename Type>
Type toY(const Range<Type>& r, Type x, Type ySize) {
    return ySize * (x - r.begin_) / r.size();
}

template <typename Type>
Type toX(const Range<Type>& r, Type y, Type ySize) {
    return r.begin_ + (y * r.size()) / ySize;
}

}  // namespace util
}  // namespace rec

