#pragma once

#include "rec/util/range/Range.h"

namespace rec {
namespace util {

// Returns the largest x such that [0, x] is covered by the container.
template <typename Type, typename Container>
Type fullTo(const Container& c) {
  return (c.empty() || c.begin()->begin_) ? Type(0) : c.begin()->end_;
}

}  // namespace util
}  // namespace rec

