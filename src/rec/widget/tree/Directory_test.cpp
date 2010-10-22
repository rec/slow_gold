#include <gtest/gtest.h>
#include <glog/logging.h>

#include "rec/widget/tree/Directory.h"

namespace rec {
namespace widget {
namespace tree {
namespace {

TEST(Directory, All) {
  Directory d(NodeDesc(), ShadowFile(File("~/iTunes"), File("~/iTunes")));
}

}  // namespace
}  // namespace tree
}  // namespace widget
}  // namespace rec
