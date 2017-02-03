#pragma once

#include "rec/base/base.h"

namespace rec {
namespace util {
namespace file {

class VirtualFile;
class VirtualFileList;

bool lessThan(const VirtualFile&, const VirtualFile&);
void sort(VirtualFileList*);

}  // namespace file
}  // namespace util
}  // namespace rec

