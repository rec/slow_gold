#ifndef __REC_UTIL_DEFAULTREGISTRY__
#define __REC_UTIL_DEFAULTREGISTRY__

#include "rec/base/base.h"

namespace rec {
namespace util {

class RegistryEntry;

class DefaultRegistry {
 public:
  DefaultRegistry() {}
  ~DefaultRegistry();

  void registerDefault(const Message&);
  void registerFile(const Message&, const VirtualFile&);
  template <typename Type> const Type& getDefault(const VirtualFile&) const;

 private:
  const Message* getDefault(const string& typeName, const VirtualFile&) const;

  typedef std::map<string, RegistryEntry*> Registry;
  RegistryEntry* get(const string&) const;
  RegistryEntry* getOrCreate(const Message&);

  Registry registry_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(DefaultRegistry);
};

template <typename Type>
const Type& DefaultRegistry::getDefault(const VirtualFile& vf) const {
  const string& name = Type::default_instance().GetTypeName();
  if (const Message* message = getDefault(name, vf)) {
    if (const Type* t = dynamic_cast<const Type*>(message))
      return *t;
    LOG(DFATAL) << "wrong type stored in defaulter";
  }
  return Type::default_instance();
}

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_DEFAULTREGISTRY__
