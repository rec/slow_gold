#include <gtest/gtest.h>

#include "rec/base/ArraySize.h"
#include "rec/util/block/FillSeries.h"

namespace rec {
namespace util {
namespace block {

TEST(WrapSeries, Simple) {
  Block b[] = {Block(5, 8), Block(10, 20)};
  BlockSet set(b, b + arraysize(b));

  BlockList fill = wrapSeries(set, 5, 2);
  EXPECT_EQ(fill.size(), 1);
  EXPECT_TRUE(*fill.begin() == Block(5, 7));
}

TEST(WrapSeries, Double) {
  Block b[] = {Block(5, 8), Block(10, 20)};
  BlockSet set(b, b + arraysize(b));

  BlockList fill = wrapSeries(set, 5, 4);
  EXPECT_EQ(fill.size(), 2);
  EXPECT_TRUE(fill[0] == Block(5, 8));
  EXPECT_TRUE(fill[1] == Block(10, 11));
}

TEST(WrapSeries, Wrap) {
  Block b[] = {Block(5, 8), Block(10, 20)};
  BlockSet set(b, b + arraysize(b));

  BlockList fill = wrapSeries(set, 5, 14);
  EXPECT_EQ(fill.size(), 3);
  EXPECT_TRUE(fill[0] == Block(5, 8));
  EXPECT_TRUE(fill[1] == Block(10, 20));
  EXPECT_TRUE(fill[2] == Block(5, 6));
}

TEST(WrapSeries, WrapWrap) {
  Block b[] = {Block(5, 8), Block(10, 20)};
  BlockSet set(b, b + arraysize(b));

  BlockList fill = wrapSeries(set, 5, 40);
  EXPECT_EQ(fill.size(), 7);
  EXPECT_TRUE(fill[0] == Block(5, 8));
  EXPECT_TRUE(fill[1] == Block(10, 20));
  EXPECT_TRUE(fill[2] == Block(5, 8));
  EXPECT_TRUE(fill[3] == Block(10, 20));
  EXPECT_TRUE(fill[4] == Block(5, 8));
  EXPECT_TRUE(fill[5] == Block(10, 20));
  EXPECT_TRUE(fill[6] == Block(5, 6));
}

TEST(FillSeries, NotEnough) {
  Block b[] = { Block(16, 37) };
  BlockSet set(b, b + arraysize(b));
  BlockList fill = fillSeries(set, 16, 67);
  EXPECT_EQ(fill.size(), 1);
  EXPECT_TRUE(fill[0] == Block(16, 37));
}

}  // namespace block
}  // namespace util
}  // namespace rec
