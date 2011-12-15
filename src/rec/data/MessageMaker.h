#ifndef __REC_DATA_MESSAGEMAKER__
#define __REC_DATA_MESSAGEMAKER__

#include <map>

#include "rec/data/TypedEditable.h"
#include "rec/util/Proto.h"
#include "rec/util/STL.h"

namespace rec {
namespace data {

class MessageMaker {
 public:
  MessageMaker() {}
  ~MessageMaker();

  Message* makeData(const string& typeName);

  template <typename Proto>
  void registerClass() {
    registerInstance(Proto::default_instance(), false);
  }

  void registerInstance(const Message& m, bool copy = true);

 private:
  typedef std::pair<Message*, bool> RegistryEntry;
  typedef std::map<string, RegistryEntry> Registry;
  Registry registry_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(MessageMaker);
};

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_MESSAGEMAKER__
