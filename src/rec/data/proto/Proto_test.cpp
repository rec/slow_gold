#include <gtest/gtest.h>

#include "rec/data/proto/TestData.pb.h"
#include "rec/data/proto/Field.h"
#include "rec/data/proto/Proto.h"
#include "rec/util/Defaulter.h"
#include "rec/gui/audio/LoopPoint.pb.h"
#include "rec/data/Operation.pb.h"

namespace rec {
namespace proto {

TEST(Proto, Apply) {
  gui::audio::LoopPointList loop_point;
  loop_point.add_loop_point()->set_time(23.5);

  Address address;
  ASSERT_TRUE(fillFromDefault("field { name: \"loop_point\" } "
                              "field { index: 0 } "
                              "field { name: \"time\"}", &address));
  Value v = getValue(address, loop_point);
  EXPECT_TRUE(v.has_double_f());
  EXPECT_EQ(v.double_f(), 23.5);
}

}  // namespace proto
}  // namespace rec
