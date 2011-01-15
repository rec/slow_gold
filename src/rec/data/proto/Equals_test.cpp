#include <gtest/gtest.h>
#include <glog/logging.h>

#include "rec/util/file/VirtualFile.h"
#include "rec/data/proto/Equals.h"

namespace rec {
namespace proto {
namespace {

TEST(Equals, get) {
  VirtualFile vf, vf2;
  EXPECT_TRUE(equals(vf, vf));

  vf2.set_type(VirtualFile::CD);
  EXPECT_FALSE(equals(vf, vf2));

  vf.CopyFrom(vf2);
  EXPECT_TRUE(equals(vf, vf));

  vf2.add_path();
  EXPECT_FALSE(equals(vf, vf2));

  vf.add_path();
  EXPECT_TRUE(equals(vf, vf2));

  vf.add_path();
  EXPECT_FALSE(equals(vf, vf2));

  vf2.add_path();
  EXPECT_TRUE(equals(vf, vf2));

  *vf.mutable_path(0) = "hello";
  EXPECT_FALSE(equals(vf, vf2));

  *vf2.mutable_path(0) = "hello";
  EXPECT_TRUE(equals(vf, vf2));
}

}  // namespace
}  // namespace proto
}  // namespace rec
