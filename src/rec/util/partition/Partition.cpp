#include "rec/util/partition/Partition.h"
#include "rec/util/partition/Compare.h"
#include "rec/util/partition/Convertors.h"

using namespace juce;

namespace rec {
namespace util {
namespace partition {
namespace {

bool isNonAlpha(int ch) {
  return isPunctuation(ch) || isdigit(ch);
}

template <typename List, typename Collection>
void doPartition(const Collection& c, const Range<int>& r, List* list) {
  Range<int> range = r;
  if (r.size() < 2) {
    LOG(ERROR) << "Can't partition very small ranges";
    return;
  }

  Range<String> name(getName(c, range.begin_), getName(c, range.end_ - 1));
  int diff = indexOfDifference(name.begin_, name.end_);
  if (diff < 0) {
    LOG(ERROR) << "Identical range";
    return;
  }

  Range<int> chars(name.begin_[diff], name.end_[diff]);
  if (!chars.begin_) {
    add(list, range.begin_);
    chars.begin_ = getName(c, ++range.begin_)[diff];
  }

  if (isNonAlpha(chars.begin_) && !isNonAlpha(chars.end_)) {
    add(list, range.begin_);
    while (isNonAlpha(range.begin_)) {
      if (++range.begin_ == range.end_)
        return;
    }
  }
  bool ascii = isASCII(getName(c, range.begin_)[diff]);
  while (range.begin_ != range.end_) {
    int x = tolower(getName(c, range.begin_)[diff]);
    if (ascii && !isASCII(x))
      break;

    add(list, range.begin_);
    while (++range.begin_ != range.end_ &&
         tolower(getName(c, range.begin_)[diff]) == x);
  }

  if (range.begin_ != range.end_)
    add(list, range.begin_);  // All the i18n as one.

    add(list, range.end_);
}

}  // namespace

template <typename List, typename Collection>
List partitionList(const Collection& col, const Range<int>& r, int mp) {
  List list;

  if (col.size() <= mp)
    addRangeToList(Range<int>(r.begin_, r.end_ + 1), &list);
  else
    doPartition(col, r, &list);

  return list;
}

template
vector<int> partitionList(const vector<string>&, const Range<int>&, int);

template
Array<int> partitionList(const Array<File>&, const Range<int>&, int);

}  // namespace partition
}  // namespace util
}  // namespace rec
