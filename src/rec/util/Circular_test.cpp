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

TEST(Circular, Consume) {
  Circular<int> c(0, 4, 8);
  c.consume(3);
  EXPECT_TRUE(c == Circular<int>(3, 4, 8));
  EXPECT_TRUE(c.fillable() == Range<int>(4, 8))
    << c.fillable().begin_ << ", " << c.fillable().end_;
}

TEST(Circular, FillAround) {
  Circular<int> c(3, 4, 8);
  c.fill(6);
  EXPECT_TRUE(c == Circular<int>(3, 10, 8)) <<
    c.begin_ << "," << c.end_ << "," << c.capacity_;

  EXPECT_TRUE(c.fillable() == Range<int>(2, 3))
    << c.fillable().begin_ << ", " << c.fillable().end_;
}

}  // namespace util
}  // namespace rec


