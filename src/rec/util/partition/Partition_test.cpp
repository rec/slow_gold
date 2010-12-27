#include <gtest/gtest.h>

#include "rec/util/partition/Partition.h"
#include "rec/base/ArraySize.h"

using std::vector;

namespace rec {
namespace util {
namespace partition {
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

  void test(int begin, int end, const char** result, int size) {
    ShardArray list = partitionList(children_, Range<int>(begin, end), 5);

#if 0
    std::cout << "test: ";
    for (int i = 0; i < list.size(); ++i)
      std::cout << list[i] << ", ";
    std::cout << std::endl;
#endif

    ASSERT_EQ(size, list.size());
    for (int i = 0; i <  list.size(); ++i)
      EXPECT_EQ(String(result[i]), list[i].name_);
  }
};

TEST_F(PartitionChildrenTest, Level1) {
  static const char* result[] = {"A", "B", "C", "D", "E", "F", "G", "H"};
  test(0, arraysize(NAMES), result, arraysize(result));
}

#if 0
TEST_F(PartitionChildrenTest, Level2) {
  static const int result[] = {5, 6, 8, 9, 10};
  test(5, 10, result, arraysize(result));
}
#endif
  
}  // namespace
}  // namespace partition
}  // namespace util
}  // namespace rec
