#ifndef __REC_DATA_DEFAULTREGISTRY__
#define __REC_DATA_DEFAULTREGISTRY__

#include "rec/base/base.h"

namespace rec {
namespace data {

class RegistryEntry;

class DefaultRegistry {
 public:
  DefaultRegistry() {}
  ~DefaultRegistry();

  void registerDefault(const Message&);
  void registerFile(const Message&, const VirtualFile&);
  const Message* getDefault(const string& typeName, const VirtualFile&);
  template <typename Type> const Type& getDefault(const VirtualFile&);

 private:
  typedef std::map<string, RegistryEntry*> Registry;
  RegistryEntry* get(const string&);
  RegistryEntry* getOrCreate(const Message&);

  Registry registry_;

  DISALLOW_COPY_AND_ASSIGN(DefaultRegistry);
};

template <typename Type>
const Type& DefaultRegistry::getDefault(const VirtualFile& vf) {
  const string& name = Type::default_instance()->GetTypeName();
  if (const Message* message = getDefault(name, vf)) {
    if (const Type* t = dynamic_cast<Type*>(message))
      return t;
    DLOG(ERROR) << "wrong type stored in defaulter";
  }
  return Type::default_instance();
}

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_DEFAULTREGISTRY__
