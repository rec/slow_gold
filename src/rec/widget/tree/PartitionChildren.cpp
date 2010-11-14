#include <vector>

#include "rec/widget/tree/PartitionChildren.h"

#include "rec/base/basictypes.h"

using namespace juce;
using std::vector;

namespace rec {
namespace widget {
namespace tree {
namespace {

template <typename Children, typename IntegerList>
void partitionChildrenT(const Children& kids, const Range& range,
                        int branch, IntegerList* list) {
  int size = range.size();
  int averageBranch = size / branch;
  int begin = range.begin_;

  add(list, begin);

  for (int i = 1; i < branch; ++i) {
    int end = range.begin_ + (size * i) / branch;
    if (end < begin + 1)
      end = begin + 1;

    if (end >= range.end_)
      break;

    int c = indexOfDifference(kids, end);
    int newEnd = end;
    for (int j = 0; end < range.end_ && c > 1 && j < averageBranch; ++j) {
      int end2 = end + (1 + j / 2) * ((j & 1) ? 1 : -1);
      if (end2 >= range.end_) {
        newEnd = range.end_;

      } else if (end2 > begin) {
        int c2 = indexOfDifference(kids, end2);
        if (c2 < c) {
          newEnd = end2;
          c = c2;
        }
      }
    }

    if (newEnd >= range.end_)
      break;

    add(list, newEnd);
    begin = newEnd;
  }

  add(list, range.end_);
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
