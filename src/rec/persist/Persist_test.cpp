#include <gtest/gtest.h>

#include "rec/base/ArraySize.h"
#include "glog/logging.h"

#include "rec/persist/Persist.h"
#include "rec/persist/testdata.pb.h"

namespace rec {
namespace persist {

using std::string;

TEST(Persist, StringPersist) {
  File file = getAppDataFile("test");
  EXPECT_TRUE(file.deleteFile());
  LOG(INFO) << "file! " << file.getFullPathName().toCString();

  typedef Persistent<TestData, google::protobuf::Message> TestPersistent;
  TestPersistent p(file);

  {
    TestPersistent::Accessor accessor(&p);
    EXPECT_EQ(accessor->foo(), 2);
    EXPECT_EQ(accessor->bar(), "baz");
    accessor->set_foo(3);
    accessor->set_bar("bang");
  }

  {
    TestPersistent::Accessor accessor(&p);
    EXPECT_EQ(accessor->foo(), 3);
    EXPECT_EQ(accessor->bar(), "bang");
  }

}

}  // namespace rec
}  // namespace cd
