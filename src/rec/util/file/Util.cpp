#include <algorithm>
#include <set>

#include "rec/util/file/Util.h"
#include "rec/base/ArraySize.h"
#include "rec/util/Compare.h"

using namespace juce;

namespace rec {
namespace util {
namespace file {

namespace {

template <typename Thread>
bool shouldExit(Thread* thread) {
  return thread && thread->threadShouldExit();
}

}  // namespace

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
  string name = str(file.getFullPathName());

#if JUCE_MAC
  eraseVolumePrefix(&name);
#endif

  return nameSet.find(name) != nameSet.end();
}

static const char* AUDIO_EXTENSIONS[] = {
  "aif",
  "aiff",
  "flac",
#if JUCE_MAC
  "m4a",
#endif
  "mp3",
  "ogg",
  "wav",
};

const char** const audioExtensions() { return AUDIO_EXTENSIONS; }
int audioExtensionCount() { return arraysize(AUDIO_EXTENSIONS); }

bool isAudio(const File& file) {
  String extension = file.getFileExtension().toLowerCase().
    trimCharactersAtStart(".");
  for (int i = 0; i < audioExtensionCount(); ++i) {
    if (String(audioExtensions()[i]) == extension)
      return true;
  }
  return false;
}

static String makePatterns() {
  StringArray s;
  String prefix("*.");
  for (int i = 0; i < audioExtensionCount(); ++i)
    s.add(prefix + audioExtensions()[i]);
  return s.joinIntoString(";");
}

const String& audioFilePatterns() {
  static const String patterns = makePatterns();
  return patterns;
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
