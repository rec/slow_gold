#include <vector>
#include <set>

#include <glog/logging.h>

#include "rec/widget/tree/PartitionChildren.h"

#include "rec/base/basictypes.h"

using namespace juce;
using std::vector;

namespace rec {
namespace widget {
namespace tree {
namespace {

struct LessThanEqualChar {
  LessThanEqualChar(int c) : c_(c) {}
  bool operator()(int c) const { return c < c_; }

  int c_;
};

template <typename Collection, typename IntList, typename Str>
class Partition {
 public:
  Partition(const Collection& k, const Range& r, int branch, IntList* list)
      : kids_(k), range_(r), branch_(branch), list_(list) {
    DCHECK_GE(branch, 2);
    partition();
  }

 private:
  void partition() {
    if (range_.size() <= branch_)
      smallPartition();
    else
      largePartition();

    if ((*list_)[list_->size() - 1] != range_.end_)
      add(range_.end_);
  }

  void smallPartition() {
    for (int i = range_.begin_; i < range_.end_; ++i)
       add(i);
  }

  int lower(int i, int d) const { return tolower(getName(i)[d]); }

  void largePartition() {
    // This is the index of the first character different between the first and
    // last entries in the names table.
    extractRange(isPunctuation);  // punctuation.
    extractRange(isdigit);  // 0-9.

    int diff = difference(range_);
    std::set<int, CompareChars> charsSet;
    for (int i = range_.begin_; i < range_.end_; ++i)
      charsSet.insert(lower(i, diff));

    typedef std::vector<int> Chars;
    Chars chars(charsSet.begin(), charsSet.end());

    int remaining = branch_ - list_->size();
    double r = chars.size() * 1.0 / remaining;

    for (int i = 0; i < remaining && range_.size() > 0; ++i)
      extractRange(LessThanEqualChar(chars[i * r]));
  }

  Str getName(int i) const;
  void add(int i);

  template <typename Operator>
  void extractRange(Operator op) {
    // This is the index of the first character different between the first and
    // last entries in the names table.
    int diff = difference(range_);
    int end = range_.end_ + (list_->size() ? 0 : -1);  // Enforce branches > 1.

    int next = range_.begin_;
    for (; next < end && op(lower(next, diff)); ++next) {}

    if (next > range_.begin_ && next < end) {
      add(range_.begin_);
      range_.begin_ = next;
    }
  }

  int difference(const Range& r) const {
    return indexOfDifference(getName(r.begin_), getName(r.end_ - 1));
  }

  const Collection& kids_;
  Range range_;
  int branch_;
  IntList* list_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Partition);
};

typedef Partition<const Array<File>, Array<int>, String>
  JucePartition;

typedef Partition<const vector<string>, vector<int>, string>
  STLPartition;


template <>
String JucePartition::getName(int i) const {
  return kids_[i].getFileName();
}

template <>
string STLPartition::getName(int i) const {
  return kids_[i];
}

template <> void JucePartition::add(int i) { list_->add(i); }
template <> void STLPartition::add(int i) { list_->push_back(i); }

}  // namespace

void partitionChildren(const Array<File>& c, const Range& r, int branch,
                       Array<int>* l) {
  JucePartition partition(c, r, branch, l);
}

void partitionChildren(const vector<string>& c, const Range& r, int branch,
                       vector<int>* l) {
  STLPartition partition(c, r, branch, l);
}


}  // namespace tree
}  // namespace widget
}  // namespace rec
