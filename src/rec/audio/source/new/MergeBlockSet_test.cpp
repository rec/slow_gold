#include <gtest/gtest.h>
#include "rec/base/ArraySize.h"
#include "rec/audio/source/new/MergeBlockSet.h"

namespace rec {
namespace buffer {

static
void expectBlockSetEqual(const BlockSet& set, Block* begin, Block* end) {
  EXPECT_EQ(set.size(), end - begin);
  for (BlockSet::iterator i = set.begin(); i != set.end() && begin != end;
       ++i, ++begin) {
    EXPECT_EQ(i->first, begin->first);
    EXPECT_EQ(i->second, begin->second);
  }
}

TEST(MergeBlockList, List) {
  BlockSet list;

  merge(makeBlock(10, 20), &list);
  {
    Block b[] = {makeBlock(10, 20)};
    expectBlockSetEqual(list, b, b + arraysize(b));
  }

  merge(makeBlock(30, 40), &list);
  {
    Block b[] = {makeBlock(10, 20), makeBlock(30, 40)};
    expectBlockSetEqual(list, b, b + arraysize(b));
  }

  merge(makeBlock(5, 9), &list);
  {
    Block b[] = {makeBlock(5, 9), makeBlock(10, 20), makeBlock(30, 40)};
    expectBlockSetEqual(list, b, b + arraysize(b));
  }

  merge(makeBlock(9, 10), &list);
  {
    Block b[] = {makeBlock(5, 20), makeBlock(30, 40)};
    expectBlockSetEqual(list, b, b + arraysize(b));
  }

  merge(makeBlock(18, 23), &list);
  {
    Block b[] = {makeBlock(5, 23), makeBlock(30, 40)};
    expectBlockSetEqual(list, b, b + arraysize(b));
  }

  merge(makeBlock(4, 42), &list);
  {
    Block b[] = {makeBlock(4, 42)};
    expectBlockSetEqual(list, b, b + arraysize(b));
  }
}

}  // namespace buffer
}  // namespace rec
