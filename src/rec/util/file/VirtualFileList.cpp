#include "rec/util/file/VirtualFileList.h"
#include "rec/util/file/VirtualFile.h"

namespace rec {
namespace util {
namespace file {

namespace {

template <typename Collection>
VirtualFileList toVirtualFileListHelper(const Collection& infiles) {
  VirtualFileList files;
  for (int i = 0; i < infiles.size(); ++i)
    files.add_file()->CopyFrom(file::toVirtualFile(infiles[i]));
  return files;
}

}  // namespace

VirtualFileList toVirtualFileList(const StringArray& files) {
  return toVirtualFileListHelper(files);
}

VirtualFileList toVirtualFileList(const juce::Array<File>& files) {
  return toVirtualFileListHelper(files);
}

}  // namespace file
}  // namespace util
}  // namespace rec
