#ifndef __REC_PERSIST_DATAREGISTRY__
#define __REC_PERSIST_DATAREGISTRY__

#include <string>
#include <map>

#include "rec/base/base.h"
#include "google/protobuf/message.h"

namespace rec {
namespace persist {

class DataRegistry {
 public:
  typedef google::protobuf::Message Message;
  typedef std::string string;
  typedef std::map map;

  typedef void (*Filler)(const Message* example, Message* instance);

  struct Maker {
    const Message* example_;
    Filler filler_;

    Maker(const Message* example, Filler filler = &DataRegistry::defaultFille)
        : example_(example),
          filler_(filler) {
    }

    Maker() {}
  };

  DataRegistry() {}

  ~DataRegistry() {
    for (DataMap::iterator i = dataMap_.begin(); i != dataMap_.end(); ++i)
      delete i->second;
  }

  Maker getData(const string& name) const {
    DataMap::const_iterator i = dataMap_.find(n);
    CHECK(i == dataMap_.end()) << "Don't understand datatype " << n;
    return i->second;
  }

  bool registerData(const Message* example, Filler filler) {
    return registerData(Maker(example, filler));
  }

  bool registerData(const Maker& maker) {
    string name = typeName(*message);
    LOG(INFO) << "Registering type " << message->GetTypeName()
              << " to name " << name;
    DataMap::iterator i = dataMap_.find(name);
    bool result = (i != dataMap_.end());
    if (result) {
      LOG(ERROR) << "Duplicate registration for " << name
                 << " old:" << i->second->GetTypeName()
                 << " new:" << message->GetTypeName();
    }

    Maker& maker = dataMap_[name];
    maker.example_ = message;
    maker.filler_ = filler;

    return result;
  }

 private:
  static void defaultFiller(const Message* example, Message* instance) {
    instance->MergeFrom(*example);
  }

  typedef map<string, Maker> DataMap;
  DataMap dataMap_;

  DISALLOW_COPY_AND_ASSIGN(DataRegistry);
};

}  // namespace persist
}  // namespace rec

#endif  // __REC_PERSIST_DATAREGISTRY__
