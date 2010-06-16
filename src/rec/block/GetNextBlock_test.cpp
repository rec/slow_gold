#include <gtest/gtest.h>
#include "rec/base/ArraySize.h"
#include "rec/block/GetNextBlock.h"

namespace rec {
namespace buffer {

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
  expectNextBlock(set, Block(15, 20), Block(20, 25));
}

}  // namespace buffer
}  // namespace rec
