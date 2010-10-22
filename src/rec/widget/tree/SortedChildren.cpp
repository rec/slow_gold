#include <algorithm>

#include "rec/widget/tree/SortedChildren.h"
#include "rec/widget/tree/Tree.h"

namespace rec {
namespace widget {
namespace tree {

namespace {

bool includeChild(const File& file) {
  // hack.
  return file.isDirectory() ||
    file.hasFileExtension("mp3") ||
    file.hasFileExtension("aiff") ||
    file.hasFileExtension("wav") ||
    file.hasFileExtension("ogg");
}

struct Compare {
  bool operator()(const File& f, const File& g) const {
    return util::utf8::cmpi(f.getFileName(), g.getFileName()) > 0;
  }
};

}  // namespace

void sortedChildren(const File& f, juce::Array<File>* kids) {
  int size = f.findChildFiles(*kids,
                              File::findFilesAndDirectories +
                              File::ignoreHiddenFiles, false);
  for (int i = 0; i < size; ++i) {
    if (!includeChild((*kids)[i]))
      kids->swap(i, --size);
  }

  kids->removeRange(size, kids->size());
  File* begin = kids->getRawDataPointer();
  File* end = begin + size;
  std::sort(begin, end, Compare());
}

}  // namespace tree
}  // namespace widget
}  // namespace rec
