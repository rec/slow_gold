#pragma once

#include "rec/base/base.h"
#include "rec/util/file/VirtualFile.pb.h"

namespace rec {
namespace util {
namespace file {

VirtualFileList toVirtualFileList(const StringArray&);
VirtualFileList toVirtualFileList(const juce::Array<File>&);

}  // namespace file
}  // namespace util
}  // namespace rec
