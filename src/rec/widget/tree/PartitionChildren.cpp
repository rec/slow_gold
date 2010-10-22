#include <vector>

#include "rec/widget/tree/PartitionChildren.h"

#include "rec/base/basictypes.h"
#include "rec/util/Utf8.h"

using namespace juce;

namespace rec {
namespace widget {
namespace tree {
namespace {

int cmpi(const Array<File>& children, int i) {
  String s(children[i - 1].getFileName());
  String t(children[i].getFileName());

  StringPiece ss(s.toUTF8(), s.length());
  StringPiece tt(t.toUTF8(), t.length());
  return rec::util::utf8::cmpi(&ss, &tt);
}

int cmpi(const std::vector<string>& kids, int i) {
  StringPiece s(kids[i - 1]);
  StringPiece t(kids[i]);
  return util::utf8::cmpi(&s, &t);
}

inline void add(Array<int>* list, int x) { list->add(x); }
inline void add(std::vector<int>* list, int x) { list->push_back(x); }

}  // namespace


template <typename Children, typename IntegerList>
void partitionChildrenT(const Children& children, const Range& range,
                        int branch, IntegerList* list) {
  int size = range.size();
  int averageBranch = size / branch;
  int begin = range.begin_;
  add(list, begin);


  for (int i = 1; i < branch; ++i) {
    int end = range.begin_ + (size * i) / branch;
    if (end < begin + 1)
      end = begin + 1;

    int c = cmpi(children, end);
    int newEnd = end;
    for (int j = 0; end < range.end_ && c > 1 && i < averageBranch; ++j) {
      int end2 = end + (1 + j / 2) * ((j & 1) ? 1 : -1);
      if (end2 >= range.end_) {
        end = range.end_;
      } else if (end2 > begin) {
        int c2 = cmpi(children, end2);
        if (c2 < c) {
          newEnd = end2;
          c = c2;
        }
      }
    }

    if (newEnd < range.end_)
      add(list, newEnd);
    else
      break;
  }
  add(list, range.end_);
}


using std::vector;

void partitionChildren(const Array<File>& c, const Range& r, int branch, Array<int>* l) {
  partitionChildrenT(c, r, branch, l);
}

void partitionChildren(const vector<string>& c, const Range& r, int branch, vector<int>* l) {
  partitionChildrenT(c, r, branch, l);
}


}  // namespace tree
}  // namespace widget
}  // namespace rec
