#ifndef __REC_UTIL_PARTITION_COMPARE__
#define __REC_UTIL_PARTITION_COMPARE__

#include "rec/base/base.h"

namespace rec {
namespace util {
namespace partition {

bool isASCII(int c);
bool isPunctuation(int c);
int compareChars(int c, int d);

struct CompareChars {
  bool operator()(int c, int d) {
    return compareChars(c, d) < 0;
  }
};

template <typename Str>
int compareStrings(const Str& x, const Str& y);

template <typename Str>
int indexOfDifference(const Str& s, const Str& t);

template <typename Collection>
int indexOfDifference(const Collection& items, const int i);

bool compareFiles(const File& f, const File& g);

}  // namespace partition
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_PARTITION_COMPARE__
