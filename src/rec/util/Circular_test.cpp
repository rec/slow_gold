#include <gtest/gtest.h>

#include "rec/util/Circular.h"

namespace rec {
namespace util {

TEST(Util, Circular) {
  Circular c(3, 8);

  EXPECT_FALSE(c.wrapsAround());
  EXPECT_EQ(c.remaining(), 8);
  EXPECT_EQ(c.remainingBlock(), 5);

  EXPECT_FALSE(c.contains(2, 0));
  EXPECT_TRUE(c.contains(3, 0));
  EXPECT_FALSE(c.contains(4, 0));

  EXPECT_FALSE(c.contains(2, 1));
  EXPECT_FALSE(c.contains(3, 1));
  EXPECT_FALSE(c.contains(4, 1));

  EXPECT_FALSE(c.contains(2, 2));
  EXPECT_FALSE(c.contains(3, 2));
  EXPECT_FALSE(c.contains(4, 2));

  c.increment(1);

  EXPECT_FALSE(c.contains(2, 0));
  EXPECT_TRUE(c.contains(3, 0));
  EXPECT_TRUE(c.contains(4, 0));

  EXPECT_FALSE(c.contains(2, 1));
  EXPECT_TRUE(c.contains(3, 1));
  EXPECT_FALSE(c.contains(4, 1));

  EXPECT_FALSE(c.contains(2, 2));
  EXPECT_FALSE(c.contains(3, 2));
  EXPECT_FALSE(c.contains(4, 2));

  c.increment(6);

  EXPECT_TRUE(c.contains(0, 0));
  EXPECT_TRUE(c.contains(1, 0));
  EXPECT_TRUE(c.contains(2, 0));
  EXPECT_TRUE(c.contains(3, 0));
  EXPECT_TRUE(c.contains(4, 0));
  EXPECT_TRUE(c.contains(5, 0));
  EXPECT_TRUE(c.contains(6, 0));
  EXPECT_TRUE(c.contains(7, 0));

  EXPECT_TRUE(c.contains(0, 1));
  EXPECT_TRUE(c.contains(1, 1));
  EXPECT_FALSE(c.contains(2, 1));
  EXPECT_TRUE(c.contains(3, 1));
  EXPECT_TRUE(c.contains(4, 1));
  EXPECT_TRUE(c.contains(5, 1));
  EXPECT_TRUE(c.contains(6, 1));
  EXPECT_TRUE(c.contains(7, 1));

  EXPECT_TRUE(c.contains(0, 2));
  EXPECT_FALSE(c.contains(1, 2));
  EXPECT_FALSE(c.contains(2, 2));
  EXPECT_TRUE(c.contains(3, 2));
  EXPECT_TRUE(c.contains(4, 2));
  EXPECT_TRUE(c.contains(5, 2));
  EXPECT_TRUE(c.contains(6, 2));
  EXPECT_TRUE(c.contains(7, 2));


}

}  // namespace util
}  // namespace rec


