#include <gtest/gtest.h>
#include <glog/logging.h>

#include "rec/util/Utf8.h"

namespace rec {
namespace util {
namespace utf8 {
namespace {

TEST(Utf8, Empty) {
  StringPiece p;
  EXPECT_EQ(decode(&p), -1);
}

TEST(Utf8, SingleItem) {
  StringPiece p("a");
  EXPECT_EQ(decode(&p), 'a');
  EXPECT_EQ(decode(&p), -1);
}

TEST(Utf8, TwoItems) {
  StringPiece p("ab");
  EXPECT_EQ(decode(&p), 'a');
  EXPECT_EQ(decode(&p), 'b');
  EXPECT_EQ(decode(&p), -1);
}

TEST(Utf8, International) {
  StringPiece p("高橋洋子");
  EXPECT_EQ(p.size(), 12);
  EXPECT_EQ(decode(&p), 563928);
  EXPECT_EQ(decode(&p), 551499);
  EXPECT_EQ(decode(&p), 552203);
  EXPECT_EQ(decode(&p), 547664);
  EXPECT_EQ(decode(&p), -1);
}


}  // namespace
}  // namespace utf8
}  // namespace util
}  // namespace rec
