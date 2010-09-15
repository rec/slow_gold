#ifndef __REC_PERSIST_DATAREGISTRY__
#define __REC_PERSIST_DATAREGISTRY__

#include <string>
#include <map>

#include "rec/base/base.h"
#include "google/protobuf/message.h"
#include "JuceLibraryCode/JuceHeader.h"

namespace rec {
namespace persist {

inline std::string typeName(const google::protobuf::Message& message) {
  std::string s(message.GetTypeName());
  s.erase(0, s.rfind(".") + 1);
  return s;
}

class DataRegistry {
 public:
  typedef google::protobuf::Message Message;
  typedef std::string string;
  typedef void (*Filler)(Message*);

  DataRegistry() {}

  ~DataRegistry() {
    for (DataMap::iterator i = dataMap_.begin(); i != dataMap_.end(); ++i)
      delete i->second;

    clearSingletonInstance();
  }

  juce_DeclareSingleton(DataRegistry, false)

  const Message* getData(const string& name) const;
  bool registerData(const Message* message);

 private:
  typedef std::map<std::string, const Message*> DataMap;
  DataMap dataMap_;

  DISALLOW_COPY_AND_ASSIGN(DataRegistry);
};

inline const google::protobuf::Message* getData(const std::string& name) {
  return DataRegistry::getInstance()->getData(name);
}

inline bool registerData(const google::protobuf::Message* message) {
  return DataRegistry::getInstance()->registerData(message);
}

}  // namespace persist
}  // namespace rec

#endif  // __REC_PERSIST_DATAREGISTRY__
