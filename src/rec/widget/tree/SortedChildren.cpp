#include <algorithm>
#include <set>

#include "rec/base/ArraySize.h"
#include "rec/widget/tree/SortedChildren.h"
#include "rec/widget/tree/Tree.h"

namespace rec {
namespace widget {
namespace tree {

namespace {

bool includeChild(const File& file) {
  // hack.
  if (file.getFileName()[0] == '.')
    return false;

  static const char* names[] = {
#if JUCE_MAC
    "/Library",
    "/OpenFolderListDF\015",
    "/Network",
    "/System",
    "/System Folder",
    "/TheVolumeSettingsFolder",
    "/Volumes",
    "/bin",
    "/cores",
    "/dev",
    "/etc",
    "/home",
    "/net",
    "/opt",
    "/private",
    "/sbin",
    "/tmp",
    "/usr",
    "/var",
#else
    // Add list of hidden files in Windows here.
    // We might also need code to deal with C:\ volume names.
#endif
  };

  static std::set<string> nameSet(names, names + arraysize(names));
  string name = file.getFullPathName().toCString();
#if JUCE_MAC
  if (name.find("/Volumes/") == 0) {
    int pos = name.find("/", strlen("/Volumes/"));
    if (pos != -1)
      name.erase(0, pos);
  }
#endif
  if (nameSet.find(name) != nameSet.end())
    return false;

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
