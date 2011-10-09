#ifndef __REC_DATA_PROTO_NAMETOPROTO__
#define __REC_DATA_PROTO_NAMETOPROTO__

#include <map>

#include "rec/data/proto/GetProtoName.h"

namespace rec {
namespace data {
namespace proto {

class NameToProto {
 public:
  NameToProto();

  void add(const Message* message) {
    ScopedLock l(lock_);
    const string& name = getName(*message);
    NameToProtoMap::iterator i = map_.find(name);
    if (i == map_.end())
      map_.insert(i, make_pair(name, message));
    else if (i->second != message)
      LOG(ERROR) << "re-registering " << name;
  }

  template <typename Proto>
  void add() {
    add(&Proto::default_instance());
  }

  const Message* getProto(const string& name) {
    NameToProtoMap::iterator i = map_.find(name);
    if (i == map_.end()) {
      DLOG(ERROR) << "Couldn't get proto for " << name;
      return NULL;
    }
    return i->second;
  }

 private:
  typedef std::map<string, const Message*> NameToProtoMap;

  CriticalSection lock_;
  NameToProtoMap map_;

  DISALLOW_COPY_AND_ASSIGN(NameToProto);
};

}  // namespace proto
}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_PROTO_NAMETOPROTO__
