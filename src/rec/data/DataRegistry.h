#ifndef __REC_DATA_DATAREGISTRY__
#define __REC_DATA_DATAREGISTRY__

#include <map>

#include "rec/util/STL.h"

namespace rec {
namespace data {

class UntypedEditable;

UntypedEditable* getUntypedData(const string& typeName, const Address&,
                                const VirtualFile& f = file::none());

class Maker {
 public:
  Maker() {}
  virtual ~Maker() {}

  virtual UntypedEditable* make(const File&, const VirtualFile&) = 0;
};

template <typename Proto>
class TypedMaker : public Maker {
 public:
  TypedMaker() {}
  virtual ~TypedMaker() {}

  virtual UntypedEditable* make(const File& f, const VirtualFile& vf) {
    return new TypedEditable<Proto>(f, vf);
  }
};

class DataRegistry {
 public:
  DataRegistry() {}
  ~DataRegistry() {
    stl::deleteMapPointers(&registry_);
  }

  template <typename Proto>
  void registerMaker() {
    const string& name = Proto::default_instance().GetTypeName();
    Registry::iterator i = registry_.find(name);
    if (i == registry_.end())
      registry_.insert(i, std::make_pair(name, new TypedMaker<Proto>()));
  }

  UntypedEditable* make(const string& name, const File& file,
                        const VirtualFile& vf) {
    Registry::iterator i = registry_.find(name);
    return (i == registry_.end()) ? NULL : i->second->make(file, vf);
  }

 private:
  typedef std::map<string, Maker*> Registry;
  Registry registry_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(DataRegistry);
};

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_DATAREGISTRY__
