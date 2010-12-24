#include <algorithm>
#include <set>

#include "rec/widget/tree/SortedChildren.h"
#include "rec/base/ArraySize.h"
#include "rec/util/ShouldExit.h"
#include "rec/widget/tree/VolumeFile.h"
#include "rec/util/partition/Compare.h"

using namespace juce;

namespace rec {
namespace widget {
namespace tree {

bool isHiddenFile(const File& file) {
  if (file.getFileName()[0] == '.')
    return true;

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
    "RECYCLER",
    "System Volume Information",
    // We might also need code to deal with volume names like C:\.
#endif
  };

  static std::set<string> nameSet(names, names + arraysize(names));
  string name = file.getFullPathName().toCString();

#if JUCE_MAC
  eraseVolumePrefix(&name);
#endif

  return nameSet.find(name) != nameSet.end();
}

bool isAudioFileOrDirectory(const File& file) {
  return !isHiddenFile(file) &&
    (file.isDirectory() ||
     file.hasFileExtension("mp3") ||
     file.hasFileExtension("aiff") ||
     file.hasFileExtension("wav") ||
     file.hasFileExtension("ogg"));
}

bool sortedChildren(const File& f, Array<File>* kids, FileFilter* filter) {
  Thread* thread = Thread::getCurrentThread();
  DirectoryIterator i(f, false, "*", File::findFilesAndDirectories);
  while (!shouldExit(thread) && i.next()) {
    File f(i.getFile());
    if (filter(f))
      kids->add(f);
  }

  if (!shouldExit(thread)) {
    File* begin = kids->getRawDataPointer();
    File* end = begin + kids->size();
    std::sort(begin, end, partition::compareFiles);
  }

  return !shouldExit(thread);
}

}  // namespace tree
}  // namespace widget
}  // namespace rec
