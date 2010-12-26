#ifndef __REC_UTIL_PARTITION_PARTITION__
#define __REC_UTIL_PARTITION_PARTITION__

#include <set>

#include "rec/util/Range.h"
#include "rec/util/partition/Compare.h"

namespace rec {
namespace util {
namespace partition {

template <typename List, typename Collection>
List partitionList(const Collection& collection,
                   const Range<int>& range,
                   int minimumPartition);

}  // namespace partition
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_PARTITION_PARTITION__
