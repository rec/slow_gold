#include <gtest/gtest.h>

#include "rec/data/yaml/Yaml.h"

#include "rec/data/Operation.pb.h"

namespace rec {
namespace yaml {
namespace {

using data::Operation;

const static char RESULT[] =
  "---\n"
  "type: rec.proto.Operation\n"
  "value:\n"
  "  command: APPEND\n"
  "  address: {field: [{index: 3}, {name: fred}]}\n"
  "  value:\n"
  "    - {uint32_f: 5}";

TEST(Yaml, Write) {
  Operation op;
  op.set_command(Operation::APPEND);
  op.mutable_address()->add_field()->set_index(3);
  op.mutable_address()->add_field()->set_name("fred");
  op.add_value()->set_uint32_f(5);

  EXPECT_EQ(RESULT, write(op));
}

TEST(Yaml, Read) {
  Operation op;
  ASSERT_TRUE(read(RESULT, &op));

  EXPECT_EQ(op.command(), Operation::APPEND);
  ASSERT_EQ(op.address().field_size(), 2);
  ASSERT_EQ(op.value_size(), 1);
  EXPECT_EQ(op.address().field(0).index(), 3);
  EXPECT_EQ(op.address().field(1).name(), "fred");
  EXPECT_EQ(op.value(0).uint32_f(), 5);
}

}  // namespace
}  // namespace yaml
}  // namespace rec
