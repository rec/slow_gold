#ifndef __REC_UTIL_WRAPSERIES__
#define __REC_UTIL_WRAPSERIES__

#include "rec/util/range/Range.h"
#include "rec/util/range/Insert.h"

namespace rec {
namespace util {

enum FillWrapping { STOP_AT_END, WRAP };

template <typename Container, typename Type>
Container fillSeries(const Container& sel, Type pos, Type len, FillWrapping w) {
  Container result;
  if (len && !sel.empty()) {
    typename Container::const_iterator i = sel.begin();
    for (; i != sel.end() && (i->end_ <= pos); ++i);

    for (uint j = 0; len > 0 && (w == WRAP || j < sel.size()); ++i, ++j) {
      if (i == sel.end()) {
        i = sel.begin();
        pos = i->begin_;
      } else {
        pos = std::max(pos, i->begin_);
      }
      Type size = std::min(len, Type(i->end_ - pos));
      DCHECK(size > 0); //  << sel; // TODO
      if (size <= 0)
        break;
      insertRange(&result, Range<Type>(pos, pos + size));
      len -= size;
    }
  }
  return result;
}

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_WRAPSERIES__
