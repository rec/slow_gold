#include "rec/util/partition/Partition.h"
#include "rec/util/partition/Compare.h"

using namespace juce;

namespace rec {
namespace util {
namespace partition {
namespace {

string getName(const File& f) { return f.getFileName().toCString(); }
string getName(const string& s) { return s; }

template <typename Collection>
string getName(const Collection& v, int i) { return getName(v[i]); }

bool isNonAlpha(int ch) {
  return isPunctuation(ch) || isdigit(ch);
}

void add(Array<int>* list, int x) { list->add(x); }
void add(vector<int>* list, int x) { list->push_back(x); }

template <typename Collection, typename IntList>
void doPartition(const Collection& c, const Range<int>& r, IntList* list) {
  Range<int> range = r;
  if (r.size() < 2) {
    LOG(ERROR) << "Can't partition very small ranges";
    return;
  }

  Range<string> name(getName(c, range.begin_), getName(c, range.end_ - 1));
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

vector<int> partitionList(const vector<string>& col, const Range<int>& range) {
  vector<int> list;
  doPartition(col, range, &list);
  return list;
}

Array<int> partitionList(const Array<File>& col, const Range<int>& range) {
  Array<int> list;
  doPartition(col, range, &list);
  return list;
}

}  // namespace partition
}  // namespace util
}  // namespace rec
