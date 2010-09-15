#ifndef __REC_PERSIST_DATAREGISTRY__
#define __REC_PERSIST_DATAREGISTRY__

#include <string>
#include <map>

#include "rec/base/base.h"
#include "google/protobuf/message.h"
#include "JuceLibraryCode/JuceHeader.h"

namespace rec {
namespace persist {

class DataRegistry {
 public:
  typedef google::protobuf::Message Message;
  typedef std::string string;
  typedef void (*Filler)(Message*);

  DataRegistry() {}

  ~DataRegistry() {
    for (DataMap::iterator i = dataMap_.begin(); i != dataMap_.end(); ++i)
      delete i->second;

    deleteInstance();
  }

  Message* createData(const string& name) const;
  bool registerData(const Message* message, const string* name = NULL);

  juce_DeclareSingleton(DataRegistry, false)

 private:
  typedef std::map<std::string, const Message*> DataMap;
  DataMap dataMap_;

  DISALLOW_COPY_AND_ASSIGN(DataRegistry);
};

inline google::protobuf::Message* createData(const std::string& name) {
  return DataRegistry::getInstance()->createData(name);
}

inline bool registerData(const google::protobuf::Message* message, 
                         const std::string* name = NULL) {
  return DataRegistry::getInstance()->registerData(message, name);
}


}  // namespace persist
}  // namespace rec

#endif  // __REC_PERSIST_DATAREGISTRY__
