#ifdef FIX_TESTS

#include <gtest/gtest.h>

#include "rec/data/proto/TestData.pb.h"
#include "rec/data/proto/Field.h"
#include "rec/util/Defaulter.h"
#include "rec/util/LoopPoint.pb.h"
#include "rec/data/Operation.pb.h"

namespace rec {
namespace data {

TEST(Proto, Apply) {
    LoopPointList loop_point;
    loop_point.add_loop_point()->set_time(23);

    Address address;
    ASSERT_TRUE(fillFromDefault("part { name: \"loop_point\" } "
                                                            "part { index: 0 } "
                                                            "part { name: \"time\"}", &address));
    Value v = getValue(address, loop_point);
    EXPECT_TRUE(v.has_uint32_f());
    EXPECT_EQ(v.uint32_f(), 23);
}

}  // namespace data
}  // namespace rec

#endif  // FIX_TESTS
