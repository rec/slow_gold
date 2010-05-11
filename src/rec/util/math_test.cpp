#include <gtest/gtest.h>
#include "rec/util/Math.h"

namespace rec {
namespace util {

TEST(Util, Mod) {
  EXPECT_EQ(mod(20, 5), 0);
  EXPECT_EQ(mod(23, 5), 3);
  EXPECT_EQ(mod(23, -5), 3);
  EXPECT_EQ(mod(-23, 5), 2);
  EXPECT_EQ(mod(-23, -5), 2);
}

}  // namespace util
}  // namespace rec
