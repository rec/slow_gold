#include <gtest/gtest.h>

#include "rec/util/Circular.h"

namespace rec {
namespace util {

namespace {

TEST(Circular, Constructor) {
  EXPECT_TRUE(Circular<int>(8) == Circular<int>(0, 0, 8));
}

TEST(Circular, Fillable) {
  EXPECT_TRUE(Circular<int>(8).fillable() == Range<int>(0, 8));
}

TEST(Circular, Fillable2) {
  EXPECT_TRUE(Circular<int>(0, 4, 8).fillable() == Range<int>(4, 8));
}

TEST(Circular, Fillable3) {
  EXPECT_TRUE(Circular<int>(4, 0, 8).fillable() == Range<int>(0, 4));
}

TEST(Circular, Fill) {
  Circular<int> c(8);
  c.fill(3);
  EXPECT_TRUE(c.fillable() == Range<int>(3, 8));
}



#if 0
TEST(Circular, Middle) {
  testCircular(Circular<int>(0, 4, 8), Range<int>(4, 8), Range<int>(0, 4));
}

TEST(Circular, Consume) {
  Circular<int> c(0, 4, 8);
  c.consume(3);

  EXPECT_TRUE(c == Circular<int>(3, 4, 8)) << c.begin_ << ", " << c.end_;
  EXPECT_FALSE(c.isFull());
}

TEST(Circular, End) {
  testCircular(Circular<int>(3, 4, 8), Range<int>(4, 8), Range<int>(3, 4));
}

TEST(Circular, FillAround) {
  Circular<int> c(3, 4, 8);
  c.fill(6);
  EXPECT_TRUE(c == Circular<int>(3, 10, 8)) << c.begin_ << ", " << c.end_;
  EXPECT_FALSE(c.isFull());

  c.fill(1);
  EXPECT_TRUE(c == Circular<int>(3, 11, 8)) << c.begin_ << ", " << c.end_;
  EXPECT_TRUE(c.isFull());
}

TEST(Circular, Around) {
  testCircular(Circular<int>(3, 10, 8), Range<int>(2, 3), Range<int>(3, 8));
}

TEST(Circular, ConsumeAround) {
  Circular<int> c(3, 10, 8);
  c.consume(5);

  EXPECT_TRUE(c == Circular<int>(0, 2, 8)) << c.begin_ << "," << c.end_;
  EXPECT_FALSE(c.isFull());

  c.consume(2);
  EXPECT_TRUE(c == Circular<int>(2, 2, 8)) << c.begin_ << "," << c.end_;
  EXPECT_FALSE(c.isFull());
}

TEST(Circular, Begin) {
  testCircular(Circular<int>(0, 2, 8), Range<int>(2, 8), Range<int>(0, 2));
}

#endif

}  // namespace
}  // namespace util
}  // namespace rec


