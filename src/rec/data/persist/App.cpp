#include <google/protobuf/descriptor.h>

#include "rec/data/persist/App.h"
#include "rec/util/STL.h"

namespace rec {
namespace persist {

App::App(const string& name) : name_(name) {
  appDir().createDirectory();
}

File App::appDir() const {
  return data::persist::appDirectory().getChildFile(name_.c_str());
}

App::~App() {
  stl::deleteMapPointers(&data_);
}

string App::getFileName(const string& nameRoot, const Message& instance) {
  return nameRoot + "." + getProtoName(instance);
}

const string& getProtoName(const Message& m) { return m.GetDescriptor()->name(); }

}  // namespace persist
}  // namespace rec
