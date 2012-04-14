#include <gtest/gtest.h>

#include "rec/util/FormatString.h"

namespace rec {
namespace util {
namespace {

TEST(FormatString, Trivial) {
  FormatString s("");
  EXPECT_EQ(str(s.format()), "");
}

}  // namespace
}  // namespace util
}  // namespace rec
