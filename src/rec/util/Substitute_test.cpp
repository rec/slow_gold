#include <gtest/gtest.h>

#include "rec/util/Substitute.h"

TEST(Util, Mod) {
    StringPairArray v;
    EXPECT_STREQ(substituteVariables(v, "").toCString(),
                 "");

    const char* pattern = "Reporter $alias is really ${real name}.";
    EXPECT_STREQ(substituteVariables(v, pattern).toCString(),
                 "Reporter  is really .");

    v.set("real name", "Superman");
    v.set("alias", "Clark Kent");

    EXPECT_STREQ(substituteVariables(v, pattern).toCString(),
                 "Reporter Clark Kent is really Superman.");
}
