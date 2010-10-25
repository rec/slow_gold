#ifndef __REC_WIDGET_TREE_TREE__
#define __REC_WIDGET_TREE_TREE__

#include "rec/util/BeginEnd.h"
#include "JuceLibraryCode/JuceHeader.h"

namespace rec {
namespace widget {
namespace tree {

typedef util::BeginEnd<int> Range;

inline String getName(const File& f) { return f.getFileName(); }
inline string getName(const string& s) { return s; }

inline int getLength(const string& s) { return s.size(); }
inline int getLength(const String& s) { return s.length(); }

inline String toLowerCase(const String& s) { return s.toLowerCase(); }

inline string toLowerCase(const string& s) {
  string t = s;
  for (int i = 0; i < t.size(); ++i)
    t[i] = tolower(t[i]);
  return t;
}

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
int cmpi(const Collection& items, const int i) {
  return indexOfDifference(toLowerCase(getName(items[i - 1])),
                           toLowerCase(getName(items[i])));
}

}  // namespace tree
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_TREE_TREE__
