#ifndef __REC_WIDGET_TREE_TREE__
#define __REC_WIDGET_TREE_TREE__

#include "rec/util/BeginEnd.h"
#include "rec/util/Utf8.h"
#include "JuceLibraryCode/JuceHeader.h"

namespace rec {
namespace widget {
namespace tree {

typedef util::BeginEnd<int> Range;

inline String getName(const File& f) { return f.getFileName(); }
inline string getName(const string& s) { return s; }

template <typename Children>
int cmpi(const Children& kids, int i) {
  return util::utf8::cmpi(getName(kids[i - 1]), getName(kids[i]));
}

struct ShadowFile {
  File file_;
  File shadow_;

  ShadowFile() {}
  ShadowFile(const File& f, const File& s) : file_(f), shadow_(s) {}
};

}  // namespace tree
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_TREE_TREE__
