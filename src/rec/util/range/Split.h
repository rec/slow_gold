#pragma once

#include "rec/util/range/Range.h"

namespace rec {
namespace util {

template <typename Type>
typename Range<Type>::Vector split(const Range<Type>& range,
                                                                      Type capacity) {
    typename Range<Type>::Vector ranges;
    if (range.end_ <= capacity) {
        ranges.push_back(range);
    } else {
        ranges.push_back(Range<Type>(range.begin_, capacity));
        ranges.push_back(Range<Type>(capacity, range.end_));
    }
    return ranges;
}

}  // namespace util
}  // namespace rec

