#pragma once

#include <set>

#include "rec/util/range/Range.h"
#include "rec/util/Compare.h"

namespace rec {
namespace util {
namespace partition {

struct Shard {
  String name_;
  Range<int> range_;

  Shard(String n, Range<int> r) : name_(n), range_(r) {}
  Shard() {}

  JUCE_LEAK_DETECTOR(Shard);
};

typedef juce::Array<Shard> ShardArray;

template <typename Collection>
ShardArray partitionList(const Collection& collection,
                         const Range<int>& range,
                         int minimumPartition);

}  // namespace partition
}  // namespace util
}  // namespace rec

