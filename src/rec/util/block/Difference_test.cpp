#include <gtest/gtest.h>
#include "rec/base/ArraySize.h"
#include "rec/util/block/Difference.h"

namespace rec {
namespace util {
namespace block {

TEST(Difference, NoIntersect) {
  Block b[] = {Block(5, 8), Block(10, 20)};
  BlockSet set(b, b + arraysize(b));

  BlockSet diff = difference(Block(0, 5), set);
  EXPECT_EQ(diff.size(), 1);
  EXPECT_TRUE(*diff.begin() == Block(0, 5));
}

TEST(Difference, Intersect) {
  Block b[] = {Block(5, 8), Block(10, 20)};
  BlockSet set(b, b + arraysize(b));

  BlockSet diff = difference(Block(0, 10), set);
  EXPECT_EQ(diff.size(), 2);
  BlockSet::const_iterator i = diff.begin();
  EXPECT_TRUE(*i++ == Block(0, 5));
  EXPECT_TRUE(*i++ == Block(8, 10));
}

TEST(Difference, Big) {
  Block b[] = {Block(5, 8), Block(10, 20)};
  BlockSet set(b, b + arraysize(b));

  BlockSet diff = difference(Block(0, 15), set);
  EXPECT_EQ(diff.size(), 2);
  BlockSet::const_iterator i = diff.begin();
  EXPECT_TRUE(*i == Block(0, 5));
  EXPECT_TRUE(*++i == Block(8, 10));
}

TEST(Difference, Biggest) {
  Block b[] = {Block(5, 8), Block(10, 20)};
  BlockSet set(b, b + arraysize(b));

  BlockSet diff = difference(Block(0, 30), set);
  EXPECT_EQ(diff.size(), 3);
  BlockSet::const_iterator i = diff.begin();
  EXPECT_TRUE(*i == Block(0, 5));
  EXPECT_TRUE(*++i == Block(8, 10));
  EXPECT_TRUE(*++i == Block(20, 30));
}

TEST(Difference, BugInCode) {
  Block b[] = {Block(0, 87)};
  BlockSet set(b, b + arraysize(b));

  BlockSet diff = difference(Block(0, 86), set);
  EXPECT_EQ(diff.size(), 0);
  LOG(ERROR) << diff;
}

TEST(Difference, BugInCode2) {
  Block b[] = {Block(0, 86458368)};
  BlockSet set1(b, b + arraysize(b));

  Block b2[] = {Block(0, 86453757)};
  BlockSet set2(b2, b2 + arraysize(b2));

  BlockSet diff = difference(set1, set2);
  EXPECT_EQ(diff.size(), 1);
  EXPECT_TRUE(*(diff.begin()) == Block(86453757, 86458368));

  diff = difference(set2, set1);
  EXPECT_EQ(diff.size(), 0);
}

TEST(Different, Sets) {
  Block a[] = {Block(86453757, 148095673)};
  Block b[] = {Block(86453757, 99413501),
               Block(113340852, 113357236),
               Block(130581433, 134939577)};
  BlockSet sel(a, a + arraysize(a));
  BlockSet filled(b, b + arraysize(b));

  BlockSet diff = difference(sel, filled);
  EXPECT_EQ(diff.size(), 3);
  BlockSet::const_iterator i = diff.begin();
  EXPECT_TRUE(*i == Block(99413501, 113340852));
  EXPECT_TRUE(*++i == Block(113357236, 130581433));
  EXPECT_TRUE(*++i == Block(134939577, 148095673));
}

TEST(firstEmptyBlockAfter, Begin) {
  Block b[] = {Block(5, 8), Block(10, 20)};
  BlockSet set(b, b + arraysize(b));
  Block res = firstEmptyBlockAfter(set, 0, 30);
  EXPECT_TRUE(res == Block(0, 5));
}

TEST(firstEmptyBlockAfter, Intersect2) {
  Block b[] = {Block(5, 8), Block(10, 20)};
  BlockSet set(b, b + arraysize(b));
  Block res = firstEmptyBlockAfter(set, 3, 30);
  EXPECT_TRUE(res == Block(3, 5));
}

TEST(firstEmptyBlockAfter, Subset1) {
  Block b[] = {Block(5, 8), Block(10, 20)};
  BlockSet set(b, b + arraysize(b));
  Block res = firstEmptyBlockAfter(set, 5, 30);
  EXPECT_TRUE(res == Block(8, 10));
}

TEST(firstEmptyBlockAfter, Intersect3) {
  Block b[] = {Block(5, 8), Block(10, 20)};
  BlockSet set(b, b + arraysize(b));
  Block res = firstEmptyBlockAfter(set, 5, 30);
  EXPECT_TRUE(res == Block(8, 10));
}

TEST(firstEmptyBlockAfter, Intersect4) {
  Block b[] = {Block(5, 8), Block(10, 20)};
  BlockSet set(b, b + arraysize(b));
  Block res = firstEmptyBlockAfter(set, 5, 30);
  EXPECT_TRUE(res == Block(8, 10));
}

TEST(firstEmptyBlockAfter, End1) {
  Block b[] = {Block(5, 8), Block(10, 20)};
  BlockSet set(b, b + arraysize(b));
  Block res = firstEmptyBlockAfter(set, 20, 30);
  EXPECT_TRUE(res == Block(20, 30));
}

TEST(firstEmptyBlockAfter, End2) {
  Block b[] = {Block(5, 8), Block(10, 20)};
  BlockSet set(b, b + arraysize(b));
  Block res = firstEmptyBlockAfter(set, 28, 30);
  EXPECT_TRUE(res == Block(28, 30));
}

TEST(firstEmptyBlockAfter, End3) {
  Block b[] = {Block(5, 8), Block(10, 30)};
  BlockSet set(b, b + arraysize(b));
  Block res = firstEmptyBlockAfter(set, 28, 30);
  EXPECT_TRUE(res == Block(0, 5));
}

TEST(firstEmptyBlockAfter, End4) {
  Block b[] = {Block(0, 3), Block(10, 30)};
  BlockSet set(b, b + arraysize(b));
  Block res = firstEmptyBlockAfter(set, 28, 30);
  EXPECT_TRUE(res == Block(3, 10)) << res.first << ", " << res.second;
}

}  // namespace block
}  // namespace util
}  // namespace rec


