#pragma once

#include "rec/util/range/Range.h"

namespace rec {
namespace util {

template <typename Type>
Type restrict(const Range<Type>& r, Type x) {
    return (x < r.begin_) ? r.begin_ : (x > r.end_) ? r.end_ : x;
}

}  // namespace util
}  // namespace rec

