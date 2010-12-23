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

bool isPunctuation(int c);
int compareChars(int c, int d);
bool compareFiles(const File& f, const File& g);

template <typename Str>
int compareStrings(const Str& x, const Str& y);

template <typename Collection>
int indexOfDifference(const Collection& items, const int i);

}  // namespace partition
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_PARTITION_PARTITIONCHILDREN__
