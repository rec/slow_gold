#ifndef __REC_UTIL_WRAPSERIES__
#define __REC_UTIL_WRAPSERIES__

#include "rec/util/range/Range.h"
#include "rec/util/range/Insert.h"

namespace rec {
namespace util {

enum FillWrapping { STOP_AT_END, WRAP };

template <typename Container, typename Type>
Container fillSeries(const Container& sel, Type pos, Type len, FillWrapping wf) {
  Container result;
  if (len && !sel.empty()) {
    Container::const_iterator i = sel.begin();
    for (; i != sel.end() && (i->second <= pos); ++i);

    for (uint j = 0; len > 0 && (wf == WRAP || j < sel.size()); ++i, ++j) {
      if (i == sel.end()) {
        i = sel.begin();
        pos = i->first;
      } else {
        pos = std::max(pos, i->first);
      }
      Type size = std::min(len, i->second - pos);
      DCHECK(size > 0) << sel;
      if (size <= 0)
        break;
      insert(&result, Range<Type>(pos, pos + size));
      len -= size;
    }
  }
  return result;
}

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_WRAPSERIES__
