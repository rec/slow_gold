#if 0
#include <gtest/gtest.h>

#include "rec/util/Circular.h"

namespace rec {
namespace util {

namespace {

typedef int64 Result[8];

void testAvailable(const Circular& c, Result result) {
  for (int i = 0; i < 8; ++i)
    EXPECT_EQ(c.availableFrom(i), result[i]);
}

}

TEST(Util, Circular) {
  Circular c(3, 8);

  EXPECT_EQ(c.remainingBlock(), 5);

  Result r1 = {-5, -6, -7, 0, -1, -2, -3, -4};
  testAvailable(c, r1);

  c.fill(1);
  EXPECT_EQ(c.remainingBlock(), 4);
  Result r2 = {-4, -5, -6, 1, 0, -1, -2, -3};
  testAvailable(c, r2);

  c.fill(6);
  EXPECT_EQ(c.remainingBlock(), 1);
  Result r3 = {2, 1, 0, 7, 6, 5, 4, 3};
  testAvailable(c, r3);

  c.fill(6);
  EXPECT_EQ(c.remainingBlock(), 0);
  Result r4 = {8, 8, 8, 8, 8, 8, 8, 8};
  testAvailable(c, r4);

  c.reset(3, 8);
  EXPECT_EQ(c.filled(), 0);
  c.fill(4);
  EXPECT_EQ(c.filled(), 4);
  EXPECT_EQ(c.remainingBlock(), 1);

  c.consume(3);
  EXPECT_EQ(c.filled(), 1);
  EXPECT_EQ(c.remainingBlock(), 1);

  c.fill(5);
  EXPECT_EQ(c.filled(), 6);
  EXPECT_EQ(c.remainingBlock(), 2);

}

}  // namespace util
}  // namespace rec

#endif
