#pragma once

#include "rec/util/range/Range.h"

namespace rec {
namespace util {

// Return the complement of the Selection in [0, length).

template <typename Type, typename Selection>
Selection complement(const Selection& con, Type length) {
    Selection result;
    Type covered(0);

    for (Selection::const_iterator i = con.begin();
              i != con.end() && covered <= length; ++i) {
        insertRange(covered, i->begin_, &result);
        covered = i->end_;
    }

    insertRange(covered, length, &result);
    return result;
}

}  // namespace util
}  // namespace rec

