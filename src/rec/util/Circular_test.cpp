#include <gtest/gtest.h>

#include "rec/util/Circular.h"

namespace rec {
namespace util {

namespace {

void testCircular(const Circular<int>& circular,
                  const Range<int>& fillable,
                  const Range<int>& consumable) {
  Range<int> f = circular.fillable();
  EXPECT_TRUE(f == fillable)
    << f.begin_ << ", " << f.end_ << " != "
    << fillable.begin_ << ", " << fillable.end_;

  Range<int> c = circular.consumable();
  EXPECT_TRUE(c == consumable)
    << c.begin_ << ", " << c.end_ << " != "
    << consumable.begin_ << ", " << consumable.end_;
}

TEST(Circular, Constructor) {
  EXPECT_TRUE(Circular<int>(8) == Circular<int>(0, 0, 8));
}

TEST(Circular, Empty) {
  testCircular(Circular<int>(8), Range<int>(0, 8), Range<int>(0, 0));
}

TEST(Circular, Fill) {
  Circular<int> c(8);
  c.fill(4);
  EXPECT_TRUE(c == Circular<int>(0, 4, 8)) << c.begin_ << ", " << c.end_;
}

TEST(Circular, Middle) {
  testCircular(Circular<int>(0, 4, 8), Range<int>(4, 8), Range<int>(0, 4));
}

TEST(Circular, Consume) {
  Circular<int> c(0, 4, 8);
  c.consume(3);

  EXPECT_TRUE(c == Circular<int>(3, 4, 8)) << c.begin_ << ", " << c.end_;
}

TEST(Circular, End) {
  testCircular(Circular<int>(3, 4, 8), Range<int>(4, 8), Range<int>(3, 4));
}

TEST(Circular, FillAround) {
  Circular<int> c(3, 4, 8);
  c.fill(6);
  EXPECT_TRUE(c == Circular<int>(3, 10, 8)) << c.begin_ << ", " << c.end_;
}

TEST(Circular, Around) {
  testCircular(Circular<int>(3, 10, 8), Range<int>(2, 3), Range<int>(3, 8));
}

TEST(Circular, ConsumeAround) {
  Circular<int> c(3, 10, 8);
  c.consume(5);

  EXPECT_TRUE(c == Circular<int>(0, 2, 8)) << c.begin_ << "," << c.end_;
}

TEST(Circular, Begin) {
  testCircular(Circular<int>(0, 2, 8), Range<int>(2, 8), Range<int>(0, 2));
}

}  // namespace
}  // namespace util
}  // namespace rec


