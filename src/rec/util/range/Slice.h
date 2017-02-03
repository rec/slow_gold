#pragma once

#include "rec/base/base.h"

namespace rec {
namespace util {

enum SliceWrapping { DONT_WRAP, DO_WRAP };

template <typename Selection, typename Type>
Selection sliceBefore(const Selection& selection, Type t) {
    Selection result;
    typename Selection::const_iterator i = selection.begin();
    for (; i != selection.end() && i->begin_ < t; ++i)
        insertBlock(i->begin_, std::min(i->end_, t), &result);

    return result;
}

template <typename Selection, typename Type>
Selection sliceAfterOrIncluding(const Selection& selection, Type t) {
    Selection result;
    typename Selection::const_iterator i = selection.begin();
    for (; i != selection.end() && (i->end_ <= t); ++i);

    for (; i != selection.end(); ++i)
        insertBlock(std::max(i->begin_, t), i->end_, &result);

    return result;
}

template <typename Selection, typename Type>
Selection wrap(const Selection& selection, Type t) {
    return stl::concat(sliceAfterOrIncluding(selection, t),
                                          sliceBefore(selection, t));
}

}  // namespace util
}  // namespace rec
