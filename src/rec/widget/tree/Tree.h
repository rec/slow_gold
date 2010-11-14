#ifndef __REC_WIDGET_TREE_TREE__
#define __REC_WIDGET_TREE_TREE__

#include "rec/util/BeginEnd.h"
#include "rec/widget/tree/Convertors.h"

namespace rec {
namespace widget {
namespace tree {

typedef util::BeginEnd<int> Range;

struct ShadowFile {
  File file_;
  File shadow_;

  ShadowFile() {}
  ShadowFile(const File& f, const File& s) : file_(f), shadow_(s) {}
};

struct CompareFiles {
  bool operator()(const File& f, const File& g) const {
    return f.getFileName().compareIgnoreCase(g.getFileName()) < 0;
  }
};

template <typename Str>
int indexOfDifference(const Str& s, const Str& t) {
  int slength = getLength(s);
  int tlength = getLength(t);
  int min = juce::jmin(slength, tlength);
  for (int i = 0; i < min; ++i) {
    if (s[i] != t[i])
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
