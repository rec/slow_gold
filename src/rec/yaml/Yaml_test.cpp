#include <gtest/gtest.h>
#include <glog/logging.h>

#include "rec/yaml/Yaml.h"

#include "rec/proto/Operation.pb.h"

namespace rec {
namespace yaml {
namespace {

using proto::Operation;

TEST(Yaml, Write) {
  Operation op;
  op.set_command(Operation::APPEND);
  op.mutable_address()->add_field()->set_index(3);
  op.mutable_address()->add_field()->set_name("fred");
  op.add_value()->set_uint32_f(5);

  const static char RESULT[] =
    "---\n"
    "command: APPEND\n"
    "address:\n"
    "  field:\n"
    "    -\n"
    "      index: 3\n"
    "    -\n"
    "      name: fred\n"
    "value:\n"
    "  -\n"
    "    uint32_f: 5";
  EXPECT_EQ(RESULT, write(op));
}

}  // namespace
}  // namespace yaml
}  // namespace rec
