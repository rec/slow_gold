#ifndef __REC_UTIL_PARTITION_PARTITIONCHILDREN__
#define __REC_UTIL_PARTITION_PARTITIONCHILDREN__

#include "rec/util/Range.h"

namespace rec {
namespace util {
namespace partition {

void partitionChildren(const juce::Array<File>& kids,
                       const Range<int>& range,
                       int branching,
                       juce::Array<int>* partition);

void partitionChildren(const std::vector<string>& kids,
                       const Range<int>& range,
                       int branching,
                       std::vector<int>* partition);

}  // namespace partition
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_PARTITION_PARTITIONCHILDREN__
