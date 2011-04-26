#include <gtest/gtest.h>
#include <glog/logging.h>

#include "rec/util/file/VirtualFile.h"
#include "rec/data/proto/Equals.h"
#include "rec/slow/Parameters.pb.h"

namespace rec {
namespace proto {
namespace {

TEST(Equals, VirtualFile) {
  VirtualFile x, y;
  EXPECT_TRUE(equals(x, x));

  y.set_type(VirtualFile::CD);
  EXPECT_FALSE(equals(x, y));

  x.CopyFrom(y);
  EXPECT_TRUE(equals(x, x));

  y.add_path();
  EXPECT_FALSE(equals(x, y));

  x.add_path();
  EXPECT_TRUE(equals(x, y));

  x.add_path();
  EXPECT_FALSE(equals(x, y));

  y.add_path();
  EXPECT_TRUE(equals(x, y));

  *x.mutable_path(0) = "hello";
  EXPECT_FALSE(equals(x, y));

  *y.mutable_path(0) = "hello";
  EXPECT_TRUE(equals(x, y));
}

TEST(Equals, Parameters) {
  slow::Parameters x, y;
  EXPECT_TRUE(equals(x, y));

  x.mutable_file()->set_type(VirtualFile::NONE);
  EXPECT_FALSE(equals(x, y));

  x.mutable_file()->clear_type();
  EXPECT_TRUE(equals(x, y));
  EXPECT_EQ(x.file().type(), VirtualFile::NONE);

  x.mutable_stretch()->mutable_stretch()->set_disabled(true);
  EXPECT_FALSE(equals(x, y));

}

}  // namespace
}  // namespace proto
}  // namespace rec
