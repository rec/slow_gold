#include <gtest/gtest.h>
#include <glog/logging.h>

#include "rec/base/scoped_ptr.h"
#include "rec/proto/TestData.pb.h"
#include "rec/proto/Proto.h"

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

  operation->add_value()->set_double_f(2.0);
  EXPECT_TRUE(applyOperation(*operation, &test));
  EXPECT_EQ(test.test_double(), 2.0);

#if false
  EXPECT_FALSE(test.has_test2());
  operation.reset(createOperation(Operation::CREATE,
                                  test::TestData3::kTest2FieldNumber,
                                  NULL));
  EXPECT_TRUE(applyOperation(*operation, &test));
  EXPECT_TRUE(test.has_test2());
  EXPECT_FALSE(applyOperation(*operation, &test));
#endif

  operation.reset(createOperation(Operation::SET,
                                  test::TestData3::kTest2FieldNumber,
                                  test::TestData2::kTestUintFieldNumber,
                                  NULL));
  operation->add_value()->set_uint32_f(23);

  EXPECT_TRUE(applyOperation(*operation, &test));
  EXPECT_EQ(test.test2().test_uint(), 23);
}


}  // namespace proto
}  // namespace rec
