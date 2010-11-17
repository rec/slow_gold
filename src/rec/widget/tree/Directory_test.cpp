#include <gtest/gtest.h>
#include <glog/logging.h>

#include "rec/widget/tree/Directory.h"

namespace rec {
namespace widget {
namespace tree {
namespace {

TEST(Directory, All) {
  Directory d(NodeDesc(), ShadowFile(File("~/iTunes"), File("~/iTunes")), false);
  d.computeChildren();
  d.setOpen(true);

  for (int i = 0; i < d.getNumSubItems(); ++i)
    LOG(INFO) << ((Node*) d.getSubItem(i))->name();
}

}  // namespace
}  // namespace tree
}  // namespace widget
}  // namespace rec
