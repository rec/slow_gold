#include "rec/util/block/FillSeries.h"

namespace rec {
namespace util {
namespace block {

namespace {

BlockList fill(const BlockSet& sel, Size pos, Size len, bool wrap) {
  BlockList result;
  if (len && !sel.empty()) {
    BlockSet::iterator i = sel.begin();
    for (; i != sel.end() && (i->second <= pos); ++i);

    for (int j = 0; len > 0 && (wrap || j < sel.size()); ++i, ++j) {
      if (i == sel.end()) {
        i = sel.begin();
        pos = i->first;
      } else {
        pos = std::max(pos, i->first);
      }
      Size size = std::min(len, i->second - pos);
      DCHECK(size > 0) << sel;
      if (size <= 0)
        break;
      result.push_back(makeBlock(pos, pos + size));
      len -= size;
    }
  }
  return result;
}

}  // namespace

BlockList wrapSeries(const BlockSet& sel, Size pos, Size len) {
  return fill(sel, pos, len, true);
}

BlockList fillSeries(const BlockSet& sel, Size pos, Size len) {
  return fill(sel, pos, len, false);
}

}  // namespace block
}  // namespace util
}  // namespace rec
