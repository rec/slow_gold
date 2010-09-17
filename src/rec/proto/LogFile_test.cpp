#include <gtest/gtest.h>
#include <glog/logging.h>

#include "rec/proto/LogFile.h"
#include "rec/proto/Proto.pb.h"

namespace rec {
namespace proto {
namespace logfile {
namespace {

TEST(LogFile, Empty) {
  File file("/tmp/test.txt");
  file.deleteFile();

  {
    Output out(file);
  }

  {
    ASSERT_TRUE(file.exists());
    Input in(file);
    Operation op;
    EXPECT_FALSE(in.read(&op));
    EXPECT_FALSE(op.has_command());
    EXPECT_EQ(op.address_size(), 0);
    EXPECT_EQ(op.value_size(), 0);
  }
}

TEST(LogFile, OneRecord) {
  File file("/tmp/test.txt");
  file.deleteFile();

  {
    Output out(file);
    Operation op;
    op.set_command(Operation::APPEND);
    op.add_address(3);
    op.add_address(4);
    op.add_value()->set_uint32_f(5);
    out.write(op);
  }

  {
    ASSERT_TRUE(file.exists());
    Input in(file);
    Operation op;
    EXPECT_TRUE(in.read(&op));
    EXPECT_EQ(op.command(), Operation::APPEND);
    EXPECT_EQ(op.address(0), 3);
    EXPECT_EQ(op.address(1), 4);
    EXPECT_EQ(op.value(0).uint32_f(), 5);
  }
}

TEST(LogFile, TwoRecords) {
  File file("/tmp/test.txt");
  file.deleteFile();

  {
    Output out(file);

    Operation op;
    op.set_command(Operation::APPEND);
    op.add_address(3);
    op.add_address(4);
    op.add_value()->set_uint32_f(5);
    out.write(op);

    op.Clear();
    op.set_command(Operation::SWAP);
    op.add_address(1);
    op.set_swap1(2);
    op.set_swap2(3);
    out.write(op);
  }

  {
    ASSERT_TRUE(file.exists());

    Input in(file);
    Operation op;

    EXPECT_TRUE(in.read(&op));
    EXPECT_EQ(op.command(), Operation::APPEND);
    EXPECT_EQ(op.address(0), 3);
    EXPECT_EQ(op.address(1), 4);
    EXPECT_EQ(op.value(0).uint32_f(), 5);

    EXPECT_TRUE(in.read(&op));

    EXPECT_EQ(op.command(), Operation::SWAP);
    EXPECT_EQ(op.address_size(), 1);
    EXPECT_EQ(op.address(0), 1);
    EXPECT_EQ(op.value_size(), 0);
    EXPECT_EQ(op.swap1(), 2);
    EXPECT_EQ(op.swap2(), 3);
  }
}

}  // namespace
}  // namespace logfile
}  // namespace proto
}  // namespace rec
