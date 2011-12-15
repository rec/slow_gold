#ifndef __REC_DATA_MESSAGEREGISTRYANDMAKER__
#define __REC_DATA_MESSAGEREGISTRYANDMAKER__

#include <map>

#include "rec/data/MessageMaker.h"
#include "rec/data/MessageRegistry.h"

namespace rec {
namespace data {

class MessageRegistryAndMaker : public MessageRegistry, public MessageMaker {
 public:
  MessageRegistryAndMaker() {}
  virtual ~MessageRegistryAndMaker();

  virtual Message* makeMessage(const string& typeName);

  virtual void registerInstance(const Message& m, bool copy = true);

 private:
  struct Entry;
  typedef std::map<string, Entry*> Registry;

  Registry registry_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(MessageRegistryAndMaker);
};

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_MESSAGEREGISTRYANDMAKER__
