#include <gtest/gtest.h>
#include <glog/logging.h>

#include "rec/util/Utf8.h"

namespace rec {
namespace util {
namespace {

TEST(Utf8, Empty) {
  StringPiece p;
  EXPECT_EQ(popUtf8Codepoint(&p), -1);
}

TEST(Utf8, SingleItem) {
  StringPiece p("a");
  EXPECT_EQ(popUtf8Codepoint(&p), 'a');
  EXPECT_EQ(popUtf8Codepoint(&p), -1);
}

TEST(Utf8, TwoItems) {
  StringPiece p("ab");
  EXPECT_EQ(popUtf8Codepoint(&p), 'a');
  EXPECT_EQ(popUtf8Codepoint(&p), 'b');
  EXPECT_EQ(popUtf8Codepoint(&p), -1);
}

}  // namespace
}  // namespace util
}  // namespace rec
