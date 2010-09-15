#include <glog/logging.h>

#include "rec/persist/DataRegistry.h"

namespace rec {
namespace persist {

using std::string;

juce_ImplementSingleton(DataRegistry)

const google::protobuf::Message* DataRegistry::getData(const string& n) const {
  DataRegistry::DataMap::const_iterator i = dataMap_.find(n);
  if (i == dataMap_.end()) {
    LOG(ERROR) << "Don't understand datatype " << n;
    return NULL;
  }

  return i->second;
}

bool DataRegistry::registerData(const Message* message) {
  string name = typeName(*message);
  LOG(INFO) << "Registering type " << message->GetTypeName()
            << " to name " << name;
  DataRegistry::DataMap::iterator i = dataMap_.find(name);
  bool result = (i != dataMap_.end());
  if (result) {
    LOG(ERROR) << "Duplicate registration for " << name
               << " old:" << i->second->GetTypeName()
               << " new:" << message->GetTypeName();
  }

  dataMap_[name] = message;
  return result;
}

}  // namespace persist
}  // namespace rec
