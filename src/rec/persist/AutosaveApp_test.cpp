#include <gtest/gtest.h>
#include <glog/logging.h>

#include <google/protobuf/descriptor.h>
#include "rec/persist/testdata.pb.h"
#include "rec/persist/Data.h"
#include "rec/persist/DataRegistry.h"
#include "rec/persist/AutosaveApp.h"

namespace rec {
namespace persist {

using std::string;

TEST(Persist, AutosaveApp) {
  File prefsFile = appDir("testapp/autosave.TestData");
  ASSERT_TRUE(prefsFile.deleteFile());

  registerData(new TestData());
  {
    AutosaveApp app("testapp", 10, 7);
    File file = app.getDataFile("autosave");
    prefsFile = file;
    Data<TestData>* data = app.getData<TestData>(std::string("autosave"));

    ASSERT_EQ(2, data->get().foo());
    ASSERT_EQ("baz", data->get().bar());

    {
      Data<TestData>::Access access(data);
      access->set_foo(3);
      access->set_bar("bang");
    }
  }

  {
    AutosaveApp app("testapp", 10, 7);
    Data<TestData>* data = app.getData<TestData>(std::string("autosave"));
    ASSERT_EQ(data->get().foo(), 3);
    ASSERT_EQ(data->get().bar(), "bang");
  }

  ASSERT_TRUE(prefsFile.deleteFile());
}

}  // namespace rec
}  // namespace cd
