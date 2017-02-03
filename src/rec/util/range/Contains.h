#pragma once

#include "rec/util/range/Range.h"

namespace rec {
namespace util {

template <typename Type>
bool contains(const Range<Type>& r, Type t) {
    return r.begin_ <= t && t < r.end_;
}

template <typename Container, typename Type>
bool contains(const Container& c, Type x) {
    for (typename Container::const_iterator i = c.begin(); i != c.end(); ++i) {
        if (contains(*i, x))
            return true;
    }

    return false;
}

template <typename Type>
bool intersects(const Range<Type>& x, const Range<Type>& y) {
    return contains(x, y.begin_) || contains(y, x.begin_);
}

}  // namespace util
}  // namespace rec

