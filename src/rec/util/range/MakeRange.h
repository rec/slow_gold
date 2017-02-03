#pragma once

#include "rec/util/range/Range.h"

namespace rec {
namespace util {

template <typename Container, typename Type>
Range<Type> doMakeRange(const Container& c) {
    return Range<Type>(c.empty() ? Type(0) : c.begin()->begin_,
                                          c.empty() ? Type(0) : c.rbegin()->end_);
}

template <typename Type>
Range<Type> makeRange(const typename Range<Type>::Set& x) {
    return doMakeRange<typename Range<Type>::Set, Type>(x);
}

template <typename Type>
Range<Type> makeRange(const typename Range<Type>::Vector& x) {
    return doMakeRange<typename Range<Type>::Vector, Type>(x);
}

}  // namespace util
}  // namespace rec

