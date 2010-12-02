#include <gtest/gtest.h>
#include "rec/base/ArraySize.h"
#include "rec/util/block/GetNextBlock.h"

namespace rec {
namespace util {
namespace block {

static
void expectNextBlock(const BlockSet& set, const Block& requested,
                     const Block& expected) {
  Block result = getNextBlock(requested, set);
  EXPECT_EQ(expected.first, result.first);
  EXPECT_EQ(expected.second, result.second);
}

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
  expectNextBlock(set, Block(15, 20), Block(20, 20));
}

TEST(Diff, All) {
  Block b[] = {Block(5, 8), Block(10, 20)};
  BlockSet set(b, b + arraysize(b));

  BlockSet d1 = difference(set, Block(0, 5));
  EXPECT_EQ(d1.size(), 1);
  EXPECT_TRUE(*d1.begin() == Block(0, 5));
}

}  // namespace block
}  // namespace util
}  // namespace rec

