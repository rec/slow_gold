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

TEST(Utf8, International) {
  StringPiece p("高橋洋子");
  EXPECT_EQ(p.size(), 12);
  EXPECT_EQ(popUtf8Codepoint(&p), 563928);
  EXPECT_EQ(popUtf8Codepoint(&p), 551499);
  EXPECT_EQ(popUtf8Codepoint(&p), 552203);
  EXPECT_EQ(popUtf8Codepoint(&p), 547664);
  EXPECT_EQ(popUtf8Codepoint(&p), -1);
}


}  // namespace
}  // namespace util
}  // namespace rec
