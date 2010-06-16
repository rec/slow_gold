#include <gtest/gtest.h>
#include "rec/base/ArraySize.h"
#include "rec/block/Block.h"

namespace rec {
namespace block {

namespace {

void expectNextBlock(const BlockSet& set, const Block& requested,
                     const Block& expected) {
  Block result = getNextBlock(set, requested);
  EXPECT_EQ(expected.first, result.first);
  EXPECT_EQ(expected.second, result.second);
}

void expectBlockSetEqual(const BlockSet& set, Block* begin, Block* end) {
  EXPECT_EQ(set.size(), end - begin);
  for (BlockSet::iterator i = set.begin(); i != set.end() && begin != end;
       ++i, ++begin) {
    EXPECT_EQ(i->first, begin->first);
    EXPECT_EQ(i->second, begin->second);
  }
}

}  // namespace

TEST(GetNextBlock, Empty) {
  BlockSet set;
  expectNextBlock(set, Block(0, 10), Block(0, 10));
}

TEST(GetNextBlock, Simple) {
  Block b[] = {Block(10, 20)};
  BlockSet set(b, b + arraysize(b));
  expectNextBlock(set, Block(0, 10), Block(0, 10));
  expectNextBlock(set, Block(0, 15), Block(0, 10));
  expectNextBlock(set, Block(9, 15), Block(9, 10));
  expectNextBlock(set, Block(15, 20), Block(20, 25));
}

TEST(MergeBlockSet, Set) {
  BlockSet set;

  merge(&set, Block(10, 20));
  {
    Block b[] = {Block(10, 20)};
    expectBlockSetEqual(set, b, b + arraysize(b));
  }

  merge(&set, Block(30, 40));
  {
    Block b[] = {Block(10, 20), Block(30, 40)};
    expectBlockSetEqual(set, b, b + arraysize(b));
  }

  merge(&set, Block(5, 9));
  {
    Block b[] = {Block(5, 9), Block(10, 20), Block(30, 40)};
    expectBlockSetEqual(set, b, b + arraysize(b));
  }

  merge(&set, Block(9, 10));
  {
    Block b[] = {Block(5, 20), Block(30, 40)};
    expectBlockSetEqual(set, b, b + arraysize(b));
  }

  merge(&set, Block(18, 23));
  {
    Block b[] = {Block(5, 23), Block(30, 40)};
    expectBlockSetEqual(set, b, b + arraysize(b));
  }

  merge(&set, Block(4, 42));
  {
    Block b[] = {Block(4, 42)};
    expectBlockSetEqual(set, b, b + arraysize(b));
  }
}

TEST(CoversTest, All) {
  Block b[] = {Block(10, 20), Block(30, 40)};
  BlockSet set(b, b + arraysize(b));
  EXPECT_TRUE(covers(set, Block(10, 20)));
  EXPECT_TRUE(covers(set, Block(10, 10)));
  EXPECT_TRUE(covers(set, Block(10, 11)));
  EXPECT_TRUE(covers(set, Block(30, 40)));
  EXPECT_FALSE(covers(set, Block(0, 5)));
  EXPECT_FALSE(covers(set, Block(5, 10)));
  EXPECT_FALSE(covers(set, Block(9, 10)));
  EXPECT_FALSE(covers(set, Block(10, 21)));
}

}  // namespace block
}  // namespace rec
