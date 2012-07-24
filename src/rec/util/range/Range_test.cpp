#include <gtest/gtest.h>
#include <glog/logging.h>

#include "rec/util/range/Range.h"

namespace rec {
namespace util {
namespace {

void compare(const Range<int>& x, const Range<int>& y) {
  EXPECT_EQ(x.begin_, y.begin_);
  EXPECT_EQ(x.end_, y.end_);
}

TEST(Range, inverse) {
  compare(Range<int>(0, 8).inverse(10), Range<int>(8, 10));
}

}  // namespace
}  // namespace util
}  // namespace rec
