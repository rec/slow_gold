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
  char out;
  EXPECT_EQ(1, encode('a', &out));
  EXPECT_EQ(out, 'a');
}

TEST(Utf8, TwoItems) {
  StringPiece p("aB");
  EXPECT_EQ(decode(&p), 'a');
  EXPECT_EQ(decode(&p), 'B');
  EXPECT_EQ(decode(&p), -1);
}

TEST(Utf8, Extended) {
  StringPiece p("©");
  EXPECT_EQ(decode(&p), 0xA9);
  EXPECT_EQ(decode(&p), -1);

  char out[3] = "..";
  EXPECT_EQ(encode(0xA9, out), 2);
  EXPECT_STREQ(out, "©");
}

TEST(Utf8, UpperLower) {
  EXPECT_EQ(toUpper(0xA9), 0xA9);
  EXPECT_EQ(toLower(0xA9), 0xA9);

  EXPECT_EQ(toUpper('a'), 'A');
  EXPECT_EQ(toLower('a'), 'a');

  EXPECT_EQ(toUpper('Z'), 'Z');
  EXPECT_EQ(toLower('Z'), 'z');
}

TEST(Utf8, International) {
  StringPiece p("高橋洋子");
  EXPECT_EQ(p.size(), 12);
  EXPECT_EQ(decode(&p), 39640);
  EXPECT_EQ(decode(&p), 27211);
  EXPECT_EQ(decode(&p), 27915);
  EXPECT_EQ(decode(&p), 23376);
  EXPECT_EQ(decode(&p), -1);


  char out[4] = "...";
  EXPECT_EQ(encode(39640, out), 3);
  EXPECT_STREQ(out, "高");
}

}  // namespace
}  // namespace utf8
}  // namespace util
}  // namespace rec
