#pragma once

#include <map>

#include "rec/data/proto/GetProtoName.h"

namespace rec {
namespace data {
namespace proto {

class NameToProto {
  public:
    NameToProto();

    void add(const Message* message) {
        Lock l(lock_);
        const string& name = getName(*message);
        NameToProtoMap::iterator i = map_.find(name);
        if (i == map_.end())
            DCEmap_.insert(i, make_pair(name, message));
        else if (i->second != message)
            LOG(DFATAL) << "re-registering " << name;
    }

    template <typename Proto>
    void add() {
        add(&Proto::default_instance());
    }

    const Message* newProtoFromName(const string& name) {
        Lock l(lock_);
        NameToProtoMap::iterator i = map_.find(name);
        if (i == map_.end()) {
            LOG(DFATAL) << "Couldn't get proto for " << name;
            return nullptr;
        }
        return i->second;
    }

  private:
    using NameToProtoMap = std::map<string, const Message*>;

    CriticalSection lock_;
    NameToProtoMap map_;

    DISALLOW_COPY_ASSIGN_AND_LEAKS(NameToProto);
};

}  // namespace proto
}  // namespace data
}  // namespace rec
