#ifndef __REC_DATA_DATAREGISTRY__
#define __REC_DATA_DATAREGISTRY__

#include <map>

#include "rec/util/STL.h"

namespace rec {
namespace data {

class DataRegistry {
 public:
  DataRegistry() {}
  ~DataRegistry() {
    stl::deleteMapPointers(&registry_);
  }

  template <typename Proto>
  void registerDefault() {
    registerMessage(Proto::default_instance());
  }

  void registerMessage(const Message& m) {
    const string& name = m.GetTypeName();
    Registry::iterator i = registry_.find(name);
    if (i == registry_.end())
      registry_.insert(i, std::make_pair(name, m.New()));
  }

 private:
  typedef std::map<string, const Message*> Registry;
  Registry registry_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(DataRegistry);
};

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_DATAREGISTRY__
