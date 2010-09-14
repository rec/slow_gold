#include <gtest/gtest.h>
#include <glog/logging.h>

#include "rec/proto/TestData.pb.h"
#include "rec/Proto/Proto.h"

namespace rec {
namespace proto {

TEST(Proto, CreateOperation) {
  test::TestData3 test;
  scoped_ptr<Operation> operation(createOperation(Operation::SET, NULL));

  EXPECT_EQ(operation->command(), Operation::SET);
  EXPECT_EQ(operation->address_size(), 0);
  EXPECT_FALSE(applyOperation(*operation, &test));

  operation.reset(createOperation(Operation::SET,
                                  test::TestData3::kTestDoubleFieldNumber,
                                  NULL));

  operation->mutable_value()->set_double_f(2.0);
  EXPECT_TRUE(applyOperation(*operation, &test));
  EXPECT_EQ(test.test_double(), 2.0);
}


}  // namespace proto
}  // namespace rec
