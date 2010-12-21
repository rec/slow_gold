#include <gtest/gtest.h>
#include "rec/widget/tree/Directory.h"

using namespace juce;

namespace rec {
namespace widget {
namespace tree {
namespace {

TEST(Directory, All) {
#if 0
  VolumeFile vf;
  vf.mutable_volume()->set_type(Volume::VOLUME);
  vf.add_path("~/iTunes");

  Directory d(NodeDesc(), vf);
  d.computeChildren();
  d.setOpen(true);

  for (int i = 0; i < d.getNumSubItems(); ++i)
    LOG(INFO) << ((Node*) d.getSubItem(i))->name();
#endif
}

}  // namespace
}  // namespace tree
}  // namespace widget
}  // namespace rec
