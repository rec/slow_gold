#ifndef __REC_WIDGET_TREE_TREE__
#define __REC_WIDGET_TREE_TREE__

#include "rec/util/BeginEnd.h"
#include "rec/widget/tree/Convertors.h"

namespace rec {
namespace widget {
namespace tree {

typedef util::BeginEnd<int> Range;

bool compareFiles(const File& f, const File& g);
bool isASCII(int c);
bool isPunctuation(int c);
int compareChars(int c, int d);
void eraseVolumePrefix(string* name, bool diskToo = true);

struct CompareChars {
  bool operator()(int c, int d) {
    return compareChars(c, d) < 0;
  }
};

template <typename Str>
int compareStrings(const Str& x, const Str& y) {
  for (int i = 0; ; ++i) {
    if (i >= getLength(x))
      return i >= getLength(y) ? 0 : -1;

    if (i >= getLength(y))
      return 1;

    if (int cmp = compareChars(x[i], y[i]))
      return cmp;
  }
}

template <typename Str>
int indexOfDifference(const Str& s, const Str& t) {
  int slength = getLength(s);
  int tlength = getLength(t);
  int min = juce::jmin(slength, tlength);
  for (int i = 0; i < min; ++i) {
    if (compareChars(s[i], t[i]))
      return i;
  }
  return (min == juce::jmax(slength, tlength)) ? -1 : min;
}

template <typename Collection>
int indexOfDifference(const Collection& items, const int i) {
  return indexOfDifference(toLowerCase(getName(items[i - 1])),
                           toLowerCase(getName(items[i])));
}

}  // namespace tree
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_TREE_TREE__
