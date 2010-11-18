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

#if 0
    std::cout << "test: ";
    for (int i = 0; i < list.size(); ++i)
      std::cout << list[i] << ", ";
    std::cout << std::endl;
#endif

    ASSERT_EQ(size, list.size());
    for (int i = 0; i <  list.size(); ++i)
      EXPECT_EQ(result[i], list[i]);
  }
};

TEST_F(PartitionChildrenTest, Branch2) {
  static const int result[] = {0, 4, 14};
  test(0, arraysize(NAMES), 2, result, arraysize(result));
}

TEST_F(PartitionChildrenTest, Branch3) {
  static const int result[] = {0, 2, 5, 14};
  test(0, arraysize(NAMES), 3, result, arraysize(result));
}

TEST_F(PartitionChildrenTest, Branch4) {
  static const int result[] = {0, 2, 4, 10, 14};
  test(0, arraysize(NAMES), 4, result, arraysize(result));
}

TEST_F(PartitionChildrenTest, Branch5) {
  static const int result[] = {0, 1, 3, 4, 10, 14};
  test(0, arraysize(NAMES), 5, result, arraysize(result));
}

TEST_F(PartitionChildrenTest, Branch6) {
  static const int result[] = {0, 1, 2, 4, 5, 10, 14};
  test(0, arraysize(NAMES), 6, result, arraysize(result));
}

TEST_F(PartitionChildrenTest, Branch7) {
  static const int result[] = {0, 1, 2, 3, 4, 5, 10, 14};
  test(0, arraysize(NAMES), 7, result, arraysize(result));
}

TEST_F(PartitionChildrenTest, Branch8) {
  static const int result[] = {0, 1, 2, 3, 4, 5, 10, 11, 14};
  test(0, arraysize(NAMES), 8, result, arraysize(result));
  test(0, arraysize(NAMES), 9, result, arraysize(result));
  test(0, arraysize(NAMES), 10, result, arraysize(result));
  test(0, arraysize(NAMES), 11, result, arraysize(result));
  test(0, arraysize(NAMES), 12, result, arraysize(result));
  test(0, arraysize(NAMES), 13, result, arraysize(result));
}

}  // namespace
}  // namespace tree
}  // namespace widget
}  // namespace rec
