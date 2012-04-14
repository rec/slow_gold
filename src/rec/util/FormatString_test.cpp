#include <gtest/gtest.h>

#include "rec/util/FormatString.h"

namespace rec {
namespace util {
namespace {

TEST(FormatString, Trivial) {
  FormatString s("");
  EXPECT_EQ(str(s.format()), "");
  EXPECT_EQ(s.parts().size(), 1);
  EXPECT_EQ(s.args().size(), 0);
}

TEST(FormatString, OnePart) {
  FormatString s("foo");
  EXPECT_EQ(str(s.format()), "foo");
  EXPECT_EQ(s.parts().size(), 1);
  EXPECT_EQ(s.args().size(), 0);
}

}  // namespace
}  // namespace util
}  // namespace rec
