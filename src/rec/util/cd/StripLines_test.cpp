#include <gtest/gtest.h>

#include "rec/util/cd/StripLines.h"

namespace rec {
namespace util {
namespace cd {
namespace {

TEST(StripLines, Trivial) {
  String data;
  juce::StringArray lines;
  ASSERT_EQ(stripLines(&data, &lines), 0);

  data = "a";
  ASSERT_EQ(stripLines(&data, &lines), 0);
  ASSERT_EQ(data, "a");
}

TEST(StripLines, Remaining) {
  String data("line 1\nline 2");
  juce::StringArray lines;
  ASSERT_EQ(stripLines(&data, &lines), 1);
  ASSERT_EQ(data, "line 2");
}

TEST(StripLines, Complex) {
  String data("Hello, line 1\nline 2 \rline3\r\nline4\n\n\r\n");
  juce::StringArray lines;
  ASSERT_EQ(stripLines(&data, &lines), 6);
  EXPECT_EQ(str(lines[0]), "Hello, line 1");
  EXPECT_EQ(str(lines[1]), "line 2 ");
  EXPECT_EQ(str(lines[2]), "line3");
  EXPECT_EQ(str(lines[3]), "line4");
  EXPECT_EQ(str(lines[4]), "");
  EXPECT_EQ(str(lines[5]), "");
  EXPECT_EQ(str(data), "");
}

TEST(splitLine, All) {
  StringPair p = splitLine("Kate Bush / The Dreaming", '/');
  EXPECT_EQ(p.first, "Kate Bush");
  EXPECT_EQ(p.second, "The Dreaming");
}

}  // namespace
}  // namespace cd
}  // namespace util
}  // namespace rec
