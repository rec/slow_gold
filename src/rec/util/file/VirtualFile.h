#ifndef __REC_UTIL_FILE_VIRTUALFILE__
#define __REC_UTIL_FILE_VIRTUALFILE__

#include "rec/base/base.h"
#include "rec/util/file/VirtualFile.pb.h"

namespace rec {

namespace data { template <typename Type> class TypedEditable; }

namespace util {
namespace file {

inline const VirtualFile& none() { return VirtualFile::default_instance(); }

const File getFile(const VirtualFile& file);
const File getShadowDirectory(const VirtualFile& file);

inline const File getShadowFile(const VirtualFile& pr, const String& child) {
  return getShadowDirectory(pr).getChildFile(child);
}

const String getFilename(const VirtualFile& file);
const String getDisplayName(const VirtualFile& file);
const String getFullDisplayName(const VirtualFile& file);

bool compare(const VirtualFile& x, const VirtualFile& y);
bool empty(const VirtualFile& file);

typedef data::TypedEditable<VirtualFile> VirtualFileData;

VirtualFile toVirtualFile(const File& file);
inline VirtualFile toVirtualFile(const String& s) { return toVirtualFile(File(s)); }
VirtualFileList toVirtualFileList(const StringArray& file);
VirtualFileList toVirtualFileList(const juce::Array<File>& files);

void sort(VirtualFileList* volumes);

}  // namespace file
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_FILE_VIRTUALFILE__
