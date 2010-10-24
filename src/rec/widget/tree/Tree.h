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

}  // namespace tree
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_TREE_TREE__
