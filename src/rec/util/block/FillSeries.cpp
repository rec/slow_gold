#include "rec/util/block/FillSeries.h"

namespace rec {
namespace util {
namespace block {

BlockList fillSeries(const BlockSet& selection, Size position, Size length) {
  BlockList result;
  if (!selection.empty()) {
    BlockSet::iterator i = selection.begin();
    for (; i != selection.end() && (i->second <= position); ++i);

    for (; length > 0; ++i) {
      if (i == selection.end()) {
        i = selection.begin();
        position = i->first;
      } else {
        position = std::max(position, i->first);
      }
      Size size = std::min(length, i->second - position);
      if (size <= 0) {
        // DLOG_FIRST_N(ERROR, 4) << "Empty origin!";
        /*
				for (BlockSet::iterator i = selection.begin(); i != selection.end(); ++i)
          DLOG(INFO) <<
          */
        DLOG(INFO) << selection;
        DCHECK(false);
        break;
      }
      result.push_back(makeBlock(position, position + size));
      length -= size;
    }
  }
  return result;
}

}  // namespace block
}  // namespace util
}  // namespace rec
