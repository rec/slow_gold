#include <gtest/gtest.h>

#include "rec/util/FormatString.h"

namespace rec {
namespace util {
namespace {

TEST(FormatString, Trivial) {
  FormatString s("");
  EXPECT_EQ(str(s.format()), "");
  EXPECT_EQ(1, s.parts().size());
  EXPECT_EQ(0, s.args().size());
}

TEST(FormatString, OnePart) {
  FormatString s("foo");
  EXPECT_EQ("foo", str(s.format()));
  EXPECT_EQ(1, s.parts().size());
  EXPECT_EQ(0, s.args().size());
}

TEST(FormatString, TwoParts) {
  FormatString s("foo %1 baz");
  EXPECT_EQ("foo bar baz", str(s.format("bar")));
  EXPECT_EQ(2, s.parts().size());
  EXPECT_EQ(1, s.args().size());
}

TEST(FormatString, ThreeParts) {
  FormatString s("foo %1 baz %2");
  EXPECT_EQ("foo bar baz bing", str(s.format("bar", "bing")));
  EXPECT_EQ(3, s.parts().size());
  EXPECT_EQ(2, s.args().size());
}

TEST(FormatString, ThreePartsTwoEmpty) {
  FormatString s("foo %1%2");
  EXPECT_EQ("foo barbing", str(s.format("bar", "bing")));
  EXPECT_EQ(3, s.parts().size());
  EXPECT_EQ(2, s.args().size());
}

TEST(FormatString, MissingNumber) {
  FormatString s("foo %hello");
  EXPECT_EQ("foo %hello", str(s.format()));
  EXPECT_EQ(1, s.parts().size());
  EXPECT_EQ(0, s.args().size());
}

}  // namespace
}  // namespace util
}  // namespace rec
