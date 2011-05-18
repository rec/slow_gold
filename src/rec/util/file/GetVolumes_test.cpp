#include <gtest/gtest.h>

#include "rec/util/file/GetVolumes.h"

namespace rec {
namespace util {
namespace file {

VirtualFileList getVolumes();

namespace {

TEST(GetVolumes, get) {
  VirtualFileList list = getVolumes();
#if 0
  for (int i = 0; i < list.size(); ++i)
    LOG(INFO) << list[i].DebugString();
#endif
}

}  // namespace
}  // namespace file
}  // namespace util
}  // namespace rec
