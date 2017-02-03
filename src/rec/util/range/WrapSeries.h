#pragma once

#include "rec/util/range/Range.h"
#include "rec/util/range/Merge.h"

namespace rec {
namespace util {

enum FillWrapping { STOP_AT_END, WRAP };

template <typename Type, typename Container>
Container getUnfilledBlocks(const Container& selection, Type pos, Type len, FillWrapping w) {
  Container result;
  if (len && !selection.empty()) {
    typename Container::const_iterator i = selection.begin();
    for (; i != selection.end() && (i->end_ <= pos); ++i);

    for (uint j = 0; len > 0 && (w == WRAP || j < selection.size()); ++i, ++j) {
      if (i == selection.end()) {
        i = selection.begin();
        pos = i->begin_;
      } else {
        pos = std::max(pos, i->begin_);
      }
      Type size = std::min(len, Type(i->end_ - pos));
      DCHECK(size > 0);
      if (size <= 0)
        break;
      mergeAtEnd(&result, Range<Type>(pos, pos + size));
      len -= size;
    }
  }
  return result;
}

}  // namespace util
}  // namespace rec

