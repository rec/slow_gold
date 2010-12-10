#include <gtest/gtest.h>
#include "rec/base/ArraySize.h"
#include "rec/util/block/Difference.h"

namespace rec {
namespace util {
namespace block {

TEST(Difference, NoIntersect) {
  Block b[] = {Block(5, 8), Block(10, 20)};
  BlockSet set(b, b + arraysize(b));

  BlockSet diff = difference(set, Block(0, 5));
  EXPECT_EQ(diff.size(), 1);
  EXPECT_TRUE(*diff.begin() == Block(0, 5));
}

TEST(Difference, Intersect) {
  Block b[] = {Block(5, 8), Block(10, 20)};
  BlockSet set(b, b + arraysize(b));

  BlockSet diff = difference(set, Block(0, 10));
  EXPECT_EQ(diff.size(), 2);
  BlockSet::const_iterator i = diff.begin();
  EXPECT_TRUE(*i++ == Block(0, 5));
  EXPECT_TRUE(*i++ == Block(8, 10));
}

TEST(Difference, Big) {
  Block b[] = {Block(5, 8), Block(10, 20)};
  BlockSet set(b, b + arraysize(b));

  BlockSet diff = difference(set, Block(0, 15));
  EXPECT_EQ(diff.size(), 2);
  BlockSet::const_iterator i = diff.begin();
  EXPECT_TRUE(*BlockSet::const_iterator i == Block(0, 5));
  EXPECT_TRUE(*++BlockSet::const_iterator i == Block(8, 10));
}

TEST(Difference, Biggest) {
  Block b[] = {Block(5, 8), Block(10, 20)};
  BlockSet set(b, b + arraysize(b));

  BlockSet diff = difference(set, Block(0, 30));
  EXPECT_EQ(diff.size(), 3);
  BlockSet::const_iterator i = diff.begin();
  EXPECT_TRUE(*BlockSet::const_iterator i == Block(0, 5));
  EXPECT_TRUE(*++BlockSet::const_iterator i == Block(8, 10));
  EXPECT_TRUE(*++BlockSet::const_iterator i == Block(20, 30));
}

TEST(firstEmptyBlockAfter, Begin) {
  Block b[] = {Block(5, 8), Block(10, 20)};
  BlockSet set(b, b + arraysize(b));
  Block res = firstEmptyBlockAfter(set, 0, 30);
  EXPECT_TRUE(res == Block(0, 5));
}

TEST(firstEmptyBlockAfter, Intersect) {
  Block b[] = {Block(5, 8), Block(10, 20)};
  BlockSet set(b, b + arraysize(b));
  Block res = firstEmptyBlockAfter(set, 3, 30);
  EXPECT_TRUE(res == Block(8, 10));
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
  EXPECT_TRUE(res == Block(3, 5));
}

}  // namespace block
}  // namespace util
}  // namespace rec


