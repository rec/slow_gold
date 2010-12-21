#include <gtest/gtest.h>

#include "rec/widget/tree/GetVolumes.h"

namespace rec {
namespace widget {
namespace tree {
namespace {

TEST(GetVolumes, get) {
  VolumeList list = getVolumes();
#if 0
  for (int i = 0; i < list.size(); ++i)
    LOG(INFO) << list[i].DebugString();
#endif
}

}  // namespace
}  // namespace tree
}  // namespace widget
}  // namespace rec
