#include <gtest/gtest.h>

#include "rec/util/Circular.h"

namespace rec {
namespace util {

namespace {

typedef int64 Result[8];

void testRemaining(const Circular& c, Result result) {
  for (int i = 0; i < 8; ++i)
    EXPECT_EQ(c.remaining(i), result[i]);
}

}

TEST(Util, Circular) {
  Circular c(3, 8);

  EXPECT_FALSE(c.wrapsAround());
  EXPECT_EQ(c.remaining(), 8);
  EXPECT_EQ(c.remainingBlock(), 5);

  Result r1 = {-5, -6, -7, 0, -1, -2, -3, -4};
  testRemaining(c, r1);

  c.increment(1);
  EXPECT_FALSE(c.wrapsAround());
  EXPECT_EQ(c.remaining(), 7);
  EXPECT_EQ(c.remainingBlock(), 4);
  Result r2 = {-4, -5, -6, 1, 0, -1, -2, -3};
  testRemaining(c, r2);

  c.increment(6);
  EXPECT_TRUE(c.wrapsAround());
  EXPECT_EQ(c.remaining(), 1);
  EXPECT_EQ(c.remainingBlock(), 1);
  Result r3 = {2, 1, 0, 7, 6, 5, 4, 3};
  testRemaining(c, r3);
}

}  // namespace util
}  // namespace rec


