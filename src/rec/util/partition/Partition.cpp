#include "rec/util/partition/Partition.h"
#include "rec/util/Compare.h"
#include "rec/util/partition/Convertors.h"

using namespace juce;

namespace rec {
namespace util {
namespace partition {
namespace {

bool isNonAlpha(int ch) {
  return !ch || isPunctuation(ch) || isdigit(ch);
}

void add(ShardArray* shards, const String& name, const Range<int>& range) {
  shards->add(Shard(name.toUpperCase(), range));
}

template <typename Coll>
void simplePartition(const Coll& col, const Range<int>& r, ShardArray* shards) {
  for (int i = r.begin_; i != r.end_; ++i)
    add(shards, getName(col[i]), i);
}

template <typename Coll>
void complexPartition(const Coll& col, const Range<int>& r, ShardArray* shards) {
  Range<int> range = r;
  if (r.size() < 2) {
    LOG(ERROR) << "Can't partition very small ranges";
    return;
  }

  Range<String> name(getName(col, range.begin_), getName(col, range.end_ - 1));
  int diff = indexOfDifference(name.begin_, name.end_);
  if (diff < 0) {
    LOG(ERROR) << "Identical range";
    return;
  }

  Range<int> chars(name.begin_[diff], name.end_[diff]);
  if (isNonAlpha(chars.begin_) && !isNonAlpha(chars.end_)) {
    Range<int> nonA = range;
    while (isNonAlpha(getName(col[++range.begin_])[diff]));
    nonA.end_ = range.begin_;
    add(shards, "<!-/, 0-9>", nonA);
  }

  bool ascii = isASCII(getName(col, range.begin_)[diff]);
  while (range.begin_ != range.end_) {
    String name = getName(col, range.begin_);
    int charToMatch = tolower(name[diff]);
    if (ascii && !isASCII(charToMatch)) {
      add(shards, "...", range);
      break;
    }

    Range<int> same = range;
    while (++range.begin_ != range.end_ &&
         tolower(getName(col, range.begin_)[diff]) == charToMatch);
    same.end_ = range.begin_;
    add(shards, name.substring(0, diff + 1), same);
  }
}

}  // namespace

template <typename Coll>
ShardArray partitionList(const Coll& col,
                         const Range<int>& range,
                         int minimumPartition) {
  ShardArray result;

  if (minimumPartition >= range.size())
    simplePartition(col, range, &result);
  else
    complexPartition(col, range, &result);

  return result;
}

template
ShardArray partitionList(const vector<string>&, const Range<int>&, int);

template
ShardArray partitionList(const Array<File>&, const Range<int>&, int);

}  // namespace partition
}  // namespace util
}  // namespace rec
