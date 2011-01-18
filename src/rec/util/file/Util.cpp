#include <algorithm>
#include <set>

#include "rec/util/file/Util.h"
#include "rec/base/ArraySize.h"
#include "rec/util/ShouldExit.h"
#include "rec/util/Compare.h"

using namespace juce;

namespace rec {
namespace util {
namespace file {


bool isHidden(const File& file) {
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

bool isAudio(const File& file) {
  return
    file.hasFileExtension("aiff") ||
    file.hasFileExtension("flac") ||
    file.hasFileExtension("m4a") ||
    file.hasFileExtension("mp3") ||
    file.hasFileExtension("ogg") ||
    file.hasFileExtension("wav");
}

String audioFilePatterns() {
  return "*.aiff;*.flac;*.m4a;*.mp3;*.ogg;*.wav";
}

bool isAudioOrDirectory(const File& file) {
  return !isHidden(file) && (file.isDirectory() || isAudio(file));
}

bool sortedChildren(const File& f, Array<File>* kids, Filter* filter) {
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
    std::sort(begin, end, compareFiles);
  }

  return !shouldExit(thread);
}

void eraseVolumePrefix(string* name, bool diskToo) {
  static const int len = strlen("/Volumes/");
  if (name->find("/Volumes/") == 0) {
    int pos = diskToo ? name->find("/", len) : len;
    if (pos != -1)
      name->erase(0, pos);
  }
}

}  // namespace file
}  // namespace util
}  // namespace rec
