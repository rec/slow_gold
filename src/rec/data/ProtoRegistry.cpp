#include "rec/data/ProtoRegistry.h"

namespace rec {
namespace data {

ProtoRegistry::~ProtoRegistry() {
  for (Registry::iterator i = registry_.begin(); i != registry_.end())
    delete i->second->first;
}

static Message* makeFrom(const Message& m, bool copy) {
  ptr<Message> msg(m.New());
  if (copy)
    msg->CopyFrom(m);
  return msg.transfer();
}

void ProtoRegistry::registerInstance(const Message& m, bool copy = true) {
  const string& typeName = getTypeName(m);
  Registry::iterator i = registry_.find(typeName);
  if (i != registry_.end()) {
    LOG(DFATAL) << "Tried to register the same type twice: " << typeName;
    return;
  }

  RegistryEntry re = std::make_pair(makeFrom(m, copy), copy);
  registry_.insert(i, std::make_pair(typeName, re));
}

Message* ProtoRegistry::make(const string& typeName) {
  Registry::iterator i = registry_.find(typeName);
  if (i != registry_.end())
    return makeFrom(i->
    LOG(DFATAL) << "Couldn't find data type " << typeName;
    return NULL;
  }
  retur
}


}  // namespace data
}  // namespace rec
