#include <gtest/gtest.h>
#include <glog/logging.h>

#include "rec/persist/AutosaveApp.h"
#include "rec/persist/Data.h"
#include "rec/persist/testdata.pb.h"

namespace rec {
namespace persist {

using std::string;

typedef Data<TestData> PersistentData;

static void testPersist(PersistentData* data, int foo, const char* bar) {
  PersistentData::Accessor accessor(data);

  ASSERT_EQ(accessor->foo(), foo);
  ASSERT_EQ(accessor->bar(), bar);
}

TEST(Persist, AutosaveApp) {
  {
    AutosaveApp app("autosave", 10, 7);
    File file = app.getDataFile("autosave");
    EXPECT_TRUE(file.deleteFile());
    Data<TestData>* data = app.getData<TestData>(std::string("autosave"));
    testPersist(data, 2, "baz");  // The defaults.

    {
      Data<TestData>::Accessor accessor(data);
      accessor->set_foo(3);
      accessor->set_bar("bang");
    }
  }

  AutosaveApp app("testapp", 10, 7);
  testPersist(app.getData<TestData>(std::string("autosave")), 3, "bang");
}

}  // namespace rec
}  // namespace cd
