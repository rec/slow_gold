#include <gtest/gtest.h>

#include "rec/util/Circular.h"

namespace rec {
namespace util {

namespace {

}

TEST(Circular, Constructor) {
  EXPECT_TRUE(Circular<int>(8) == Circular<int>(0, 0, 8));
}

TEST(Circular, Fillable) {
  EXPECT_TRUE(Circular<int>(8).fillable() == Range<int>(0, 8));
}

TEST(Circular, Fill) {
  Circular<int> c(8);
  c.fill(4);
  EXPECT_TRUE(c == Circular<int>(0, 4, 8));
  EXPECT_TRUE(c.fillable() == Range<int>(4, 8));
}

}  // namespace util
}  // namespace rec


