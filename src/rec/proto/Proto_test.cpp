#include <gtest/gtest.h>
#include <glog/logging.h>

#include "rec/proto/TestData.pb.h"
#include "rec/Proto/Proto.h"

namespace rec {
namespace proto {


TEST(Proto, Operation) {
  test::TestData3 test;
  Operation operation;
}


TEST(Proto, CreateOperation) {
  scoped_ptr<Operation> operation(createOperation(Operation::SET, NULL));
  EXPECT_EQ(operation->command(), Operation::SET);
  EXPECT_EQ(operation->address_size(), 0);
}


}  // namespace proto
}  // namespace rec
