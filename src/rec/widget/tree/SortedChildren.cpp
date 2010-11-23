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
}  // namespace

void sortedChildren(const File& f, juce::Array<File>* kids,
                    const juce::Thread* thread) {
  juce::DirectoryIterator i(f, false, "*", juce::File::findFilesAndDirectories);
  while (i.next()) {
    File f(i.getFile());
    if (includeChild(f))
      kids->add(f);

    if (thread && thread->threadShouldExit())
      return;
  }

  File* begin = kids->getRawDataPointer();
  File* end = begin + kids->size();
  std::sort(begin, end, compareFiles);
}

}  // namespace tree
}  // namespace widget
}  // namespace rec
