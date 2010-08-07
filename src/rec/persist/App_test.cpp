#include <gtest/gtest.h>
#include <glog/logging.h>

#include "rec/persist/App.h"
#include "rec/persist/Accessor.h"
#include "rec/persist/Data.h"
#include "rec/persist/testdata.pb.h"

namespace rec {
namespace persist {

using std::string;

static void testPersist(App* app, int foo, const char* bar) {
  TestData t;
  Data<TestData> data("testdata", app);
  Accessor<TestData> accessor(&data);

  EXPECT_EQ(accessor->foo(), foo);
  EXPECT_EQ(accessor->bar(), bar);
}

TEST(Persist, App) {
  App app("testapp");

  File file = app.getDataFile("testdata");
  EXPECT_TRUE(file.deleteFile());

  testPersist(&app, 2, "baz");  // The defaults.

  {
    Data<TestData> data("testdata", &app);
    Accessor<TestData> accessor(&data);
    accessor->set_foo(3);
    accessor->set_bar("bang");

    testPersist(&app, 2, "baz");  // Still not written yet.
  }
  testPersist(&app, 3, "bang");
}

}  // namespace rec
}  // namespace cd
