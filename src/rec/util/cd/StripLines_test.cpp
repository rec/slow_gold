#include <gtest/gtest.h>
#include <glog/logging.h>

#include "rec/util/cd/StripLines.h"
#include "JuceLibraryCode/JuceHeader.h"

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
}

TEST(StripLines, Complex) {
  String data("Hello, line 1\nline 2 \rline3\r\nline4\n\n\r\n");
  juce::StringArray lines;
  ASSERT_EQ(stripLines(data, &lines), 6);
  EXPECT_STREQ(lines[0].toCString(), "Hello, line1");
  EXPECT_STREQ(lines[1].toCString(), "line2 ");
  EXPECT_STREQ(lines[2].toCString(), "line3");
  EXPECT_STREQ(lines[3].toCString(), "line4");
  EXPECT_STREQ(lines[4].toCString(), "");
  EXPECT_STREQ(lines[5].toCString(), "");
  EXPECT_STREQ(data.toCString(), "");
}

}  // namespace
}  // namespace cd
}  // namespace util
}  // namespace rec
