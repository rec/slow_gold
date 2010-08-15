#include <gtest/gtest.h>
#include <glog/logging.h>

#include "rec/persist/AutosaveApp.h"
#include "rec/persist/Data.h"
#include "rec/persist/testdata.pb.h"

namespace rec {
namespace persist {

using std::string;

static void testPersist(Data<TestData>* data, int foo, const char* bar) {
  ASSERT_EQ(data->get().foo(), foo);
  ASSERT_EQ(data->get().bar(), bar);
}

TEST(Persist, AutosaveApp) {
  {
    AutosaveApp app("testapp", 10, 7);
    File file = app.getDataFile("autosave");
    ASSERT_TRUE(file.deleteFile());
    Data<TestData>* data = app.getData<TestData>(std::string("autosave"));
    testPersist(data, 2, "baz");  // The defaults.

    {
      Data<TestData>::Access access(data);
      access->set_foo(3);
      access->set_bar("bang");
    }
  }

  AutosaveApp app("testapp", 10, 7);
  testPersist(app.getData<TestData>(std::string("autosave")), 3, "bang");
}

}  // namespace rec
}  // namespace cd
