#ifndef __REC_UTIL_PARTITION_PARTITION__
#define __REC_UTIL_PARTITION_PARTITION__

#include <set>

#include "rec/util/Range.h"
#include "rec/util/partition/Compare.h"

namespace rec {
namespace util {
namespace partition {

struct Shard {
  String name_;
  Range<int> range_;

  Shard(String n, Range<int> r) : name_(n), range_(r) {}
  Shard() {}
};

typedef juce::Array<Shard> ShardArray;

template <typename Collection>
ShardArray partitionList(const Collection& collection,
                         const Range<int>& range,
                         int minimumPartition);

}  // namespace partition
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_PARTITION_PARTITION__
