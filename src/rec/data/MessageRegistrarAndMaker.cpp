#include <google/protobuf/message.h>

#include "rec/data/MessageRegistrarAndMaker.h"
#include "rec/util/proto/Proto.h"
#include "rec/util/STL.h"
#include "rec/util/file/VirtualFile.h"

namespace rec {
namespace data {

class MessageRegistrarAndMaker::Entry {
 public:
  Entry(const Message& m, bool c) { initialize(m, c); }
  Entry(const Entry& e) { initialize(*e.message_, e.copyFrom_); }

  Message* makeMessage() { return Entry(*this).message_.transfer(); }

 private:
  void initialize(const Message& m, bool c) {
    copyFrom_ = c;
    message_.reset(m.New());
    if (copyFrom_)
      message_->CopyFrom(m);
  }

  ptr<Message> message_;
  bool copyFrom_;

};

MessageRegistrarAndMaker::~MessageRegistrarAndMaker() {
  stl::deleteMapPointers(&registry_);
}

void MessageRegistrarAndMaker::registerInstance(const Message& m, bool copy) {
  const string& typeName = getTypeName(m);
  DCHECK_LT(typeName.size(), file::MAX_FILENANE_LENGTH);
  Registry::iterator i = registry_.find(typeName);
  if (i != registry_.end()) {
    LOG(DFATAL) << "Tried to register the same type twice: " << typeName;
    return;
  }

  registry_.insert(i, std::make_pair(typeName, new Entry(m, copy)));
}

Message* MessageRegistrarAndMaker::makeMessage(const string& typeName) {
  Registry::iterator i = registry_.find(typeName);
  if (i != registry_.end())
    return i->second->makeMessage();

  LOG(DFATAL) << "Couldn't find data type " << typeName;
  return NULL;
}

}  // namespace data
}  // namespace rec
