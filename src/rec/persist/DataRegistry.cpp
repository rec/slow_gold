#include <glog/logging.h>

#include "rec/persist/DataRegistry.h"

namespace rec {
namespace persist {

using std::string;

juce_ImplementSingleton(DataRegistry)

namespace {

}  // namespace

google::protobuf::Message* DataRegistry::createData(const string& name) const {
  DataRegistry::DataMap::const_iterator i = dataMap_.find(name);
  if (i == dataMap_.end()) {
    LOG(ERROR) << "Don't understand dataytpe " << name;
    return NULL;
  }

  const Message* message = i->second;
  Message* result = message->New();
  result->CopyFrom(*message);
  return result;
}

bool DataRegistry::registerData(const Message* message) {
  string name = lastSegment(message->GetTypeName());

  DataRegistry::DataMap::iterator i = dataMap_.find(name);
  if (i != dataMap_.end()) {
    LOG(ERROR) << "Duplicate registration for " << name
               << " old:" << i->second->GetTypeName()
               << " new:" << message->GetTypeName();
    return false;
  }

  dataMap_[name] = message;
  return true;
}

}  // namespace persist
}  // namespace rec
