#include "rec/data/MessageRegistryAndMaker.h"

namespace rec {
namespace data {

namespace {

Message* makeFrom(const Message& m, bool copy) {
}

class MessageRegistryAndMaker::Entry {
 public:
  Entry(Message* m, bool c) { initialize(m, c); }
  Entry(const Entry& e) { initialize(e.message_.get(), e.copyFrom_); }

  Message* makeMessage() { return Entry(*this).message_.transfer(); }

 private:
  void initialize(Message* m, bool c) {
    copyFrom_ = c;
    message_(m->New()),
    if (copyFrom_)
      message_->CopyFrom(m);
  }

  ptr<Message> message_;
  bool copyFrom_;

};

}  // namespace

MessageRegistryAndMaker::~MessageRegistryAndMaker() {
  stl::deleteMapPointers(&registry_);
}

void MessageRegistryAndMaker::registerInstance(const Message& m,
                                               bool copyFrom = true) {
  const string& typeName = getTypeName(m);
  Registry::iterator i = registry_.find(typeName);
  if (i != registry_.end()) {
    LOG(DFATAL) << "Tried to register the same type twice: " << typeName;
    return;
  }

  registry_.insert(i, std::make_pair(typeName, new Entry(m, copyFrom)));
}

Message* MessageRegistryAndMaker::makeMessage(const string& typeName) {
  Registry::iterator i = registry_.find(typeName);
  if (i != registry_.end())
    return *i->second->makeMessage();

  LOG(DFATAL) << "Couldn't find data type " << typeName;
  return NULL;
}


}  // namespace data
}  // namespace rec

