#include <gtest/gtest.h>

#include "rec/base/ArraySize.h"
#include "rec/persist/Persist.h"

namespace rec {
namespace persist {

TEST(Persist, StringPersist) {
  std::string storage("wombat");
  Persistent<std::string, std::string*> p(&storage);
  EXPECT_EQ(storage, "wombat");

  {
    Persistent<std::string, std::string*>::Accessor accessor(&p);
    EXPECT_EQ(*accessor, "wombat");
    *accessor = "snake";
    EXPECT_EQ(*accessor, "snake");
    EXPECT_EQ(storage, "wombat");
  }

  EXPECT_EQ(storage, "snake");
}

}  // namespace rec
}  // namespace cd
