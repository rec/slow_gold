#include <map>

#include "google/protobuf/message.h"

#include "rec/util/file/VirtualFile.h"
#include "rec/util/STL.h"

namespace rec {
namespace util {

static const char* DEFAULT_NAME = "(default)";

class RegistryEntry {
 public:
  RegistryEntry() {}
  ~RegistryEntry() { stl::deleteMapPointers(&map_); }

  void add(const Message& m, const string& name) {
    DefaultMap::iterator i = map_.find(name);
    if (i != map_.end())
      delete i->second;

    ptr<Message> copy(m.New());
    copy->CopyFrom(m);
    map_.insert(i, std::make_pair(name, copy.transfer()));
  }

  const Message* get(const string& s) const {
    DefaultMap::const_iterator i = map_.find(s);
    return (i == map_.end()) ? NULL : i->second;
  }

 private:
  typedef std::map<string, Message*> DefaultMap;
  DefaultMap map_;
};

DefaultRegistry::~DefaultRegistry() {
  stl::deleteMapPointers(&registry_);
}

RegistryEntry* DefaultRegistry::get(const string& name) const {
  Registry::const_iterator i = registry_.find(name);
  return (i == registry_.end()) ? NULL : i->second;
}

RegistryEntry* DefaultRegistry::getOrCreate(const Message& m) {
  const string& name = m.GetTypeName();
  RegistryEntry* entry = get(name);
  if (!entry)
    entry = registry_[name] = new RegistryEntry();

  return entry;
}

void DefaultRegistry::registerDefault(const Message& m) {
  getOrCreate(m)->add(m, DEFAULT_NAME);
}

void DefaultRegistry::registerFile(const Message& m, const VirtualFile& vf) {
  getOrCreate(m)->add(m, toString(vf));
}

const Message* DefaultRegistry::getDefault(const string& typeName,
                                           const VirtualFile& vf) const {
  if (RegistryEntry* entry = get(typeName)) {
    if (const Message* m = entry->get(toString(vf)))
      return m;
    if (const Message* m = entry->get(DEFAULT_NAME))
      return m;
  }

  return NULL;
}

}  // namespace util
}  // namespace rec

