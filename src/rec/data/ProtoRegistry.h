#ifndef __REC_DATA_PROTOREGISTRY__
#define __REC_DATA_PROTOREGISTRY__

#include <map>

#include "rec/data/TypedEditable.h"
#include "rec/util/Proto.h"
#include "rec/util/STL.h"

namespace rec {
namespace data {

class ProtoRegistry {
 public:
  ProtoRegistry() {}

  ~ProtoRegistry();

  template <typename Proto>
  void registerProto() {
    doRegister(Proto::default_instance(), false);
  }

  void registerInstance(const Message& m, bool copy = true);
  Message* make(const string& typeName);

 private:
  typedef std::pair<Message*, bool> RegistryEntry;
  typedef std::map<string, RegistryEntry> Registry;
  Registry registry_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(ProtoRegistry);
};

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_PROTOREGISTRY__
