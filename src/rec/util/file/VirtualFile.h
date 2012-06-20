#ifndef __REC_UTIL_FILE_VIRTUALFILE__
#define __REC_UTIL_FILE_VIRTUALFILE__

#include "rec/base/base.h"
#include "rec/util/file/VirtualFile.pb.h"

namespace rec {
namespace util {
namespace file {

inline const VirtualFile& none() {
  return VirtualFile::default_instance();
}

inline const VirtualFile global() {
  VirtualFile vf;
  vf.set_type(VirtualFile::GLOBAL);
  return vf;
}

const File getRealFile(const VirtualFile&);
const File getShadowDirectory(const VirtualFile&);

inline const File getShadowFile(const VirtualFile& pr, const String& child) {
  return getShadowDirectory(pr).getChildFile(child);
}

const String getFilename(const VirtualFile&);
const String getDisplayName(const VirtualFile&);
const String getFullDisplayName(const VirtualFile&);

inline const string toString(const VirtualFile& f) {
  return str(getFullDisplayName(f));
}

inline const string toString(const VirtualFile* f) {
  return f ? toString(*f) : string("(no file)");
}

bool compare(const VirtualFile& x, const VirtualFile& y);

VirtualFile toVirtualFile(const File& file);
VirtualFile toVirtualFile(const string& s);

VirtualFileList toVirtualFileList(const StringArray& file);
VirtualFileList toVirtualFileList(const juce::Array<File>& files);

void sort(VirtualFileList* volumes);

}  // namespace file
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_FILE_VIRTUALFILE__
