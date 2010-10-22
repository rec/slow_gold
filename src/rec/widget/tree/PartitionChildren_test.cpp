#include <vector>

#include <gtest/gtest.h>
#include <glog/logging.h>

#include "rec/widget/tree/PartitionChildren.h"
#include "rec/base/ArraySize.h"

using std::vector;

namespace rec {
namespace widget {
namespace tree {
namespace {

const char* NAMES[] = {"a", "bede", "c", "d",
                       "e", "f", "fa", "fab",
                       "fb", "fc", "g", "h",
                       "he", "hi", };

class PartitionChildrenTest : public testing::Test {
 public:
  virtual void SetUp() {
    children_.clear();
    children_.insert(children_.begin(), NAMES, NAMES + arraysize(NAMES));
  }

 protected:
  vector<string> children_;

  void test(int begin, int end, int branch, const int* result, int size) {
    vector<int> list;
    partitionChildren(children_, Range(begin, end), branch, &list);
    ASSERT_EQ(size, list.size());
    for (int i = 0; i <  list.size(); ++i)
      EXPECT_EQ(result[i], list[i]);
  }
};

TEST_F(PartitionChildrenTest, Simple) {
  static const int result[] = {0, 5, arraysize(NAMES)};
  test(0, arraysize(NAMES), 2, result, arraysize(result));
}

}  // namespace
}  // namespace tree
}  // namespace widget
}  // namespace rec
