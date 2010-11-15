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

template <typename Children>
int getChildChar(const Children& kids, int kid, int ch) {
  return getName(kids[kid])[ch];
}

template <typename Children, typename IntegerList>
void partitionChildrenT(const Children& kids, const Range& range,
                        int branch, IntegerList* list) {
  DCHECK_GE(branch, 2);

  int size = range.size();
  int child = range.begin_;
  int end = range.end_;

  if (size <= branch) {
    // List is smaller than branching.
    for (; child < range.end_; ++child)
      add(list, child);
    add(list, end);
    return;
  }

  DCHECK_GT(size, 2);

  // This is the index of the first character different between the first and
  // last entries in the names table.
  int diff = indexOfDifference(getName(kids[child]), getName(kids[end - 1]));

  // Special case: put all punctuation into one bucket if this doesn't result in
  // only one bucket.
  int punc = child;
  for (; punc < end - 1 && getChildChar(kids, punc, diff) < '0'; ++punc) {}

  if (punc != child && punc < end - 1) {
    add(list, child);
    child = punc;
    branch;
  }


  std::set<int> charsSet;
  for (int i = child; i < end; ++i)
    charsSet.insert(getChildChar(kids, i, diff));

  typedef std::vector<int> Chars;
  Chars chars(charsSet.begin(), charsSet.end());

  int remaining = branch - list->size();
  float r = (1.0 * remaining) / chars.size();

  for (int i = 0; i < remaining && child < end; ++i) {
    int ch = chars[i * r];
    for (; child < end && getChildChar(kids, child, diff) < ch; ++child) {}
    add(list, child);
  }

  if (child != end)
    add(list, end);
}

}  // namespace

void partitionChildren(const Array<File>& c, const Range& r, int branch,
                       Array<int>* l) {
  partitionChildrenT(c, r, branch, l);
}

void partitionChildren(const vector<string>& c, const Range& r, int branch,
                       vector<int>* l) {
  partitionChildrenT(c, r, branch, l);
}


}  // namespace tree
}  // namespace widget
}  // namespace rec
