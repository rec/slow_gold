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

inline bool isASCII(int c) { return c >= 0 && c <= 0xFF; }

inline bool isPunctuation(int c) {
  return isASCII(c) &&
    (c < '0' || (c > '9' && c < 'A') || (c > 'Z' && c < 'a') || c > 'z');
}

inline int compareChars(int c, int d) {
  bool pc = isPunctuation(c);
  bool pd = isPunctuation(d);

  return (pc == pd) ? (tolower(c) - tolower(d)) : (pc ? -1 : 1);
}

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

inline bool compareFiles(const File& f, const File& g) {
  return compareStrings(f.getFileName(), g.getFileName()) < 0;
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
