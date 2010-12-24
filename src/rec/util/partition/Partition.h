#ifndef __REC_UTIL_PARTITION_PARTITION__
#define __REC_UTIL_PARTITION_PARTITION__

#include <set>

#include "rec/util/Range.h"
#include "rec/util/partition/Compare.h"

namespace rec {
namespace util {
namespace partition {

vector<int> partitionList(const vector<string>&, const Range<int>&);
juce::Array<int> partitionList(const juce::Array<File>&, const Range<int>&);

}  // namespace partition
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_PARTITION_PARTITION__
