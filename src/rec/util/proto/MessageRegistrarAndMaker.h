#ifndef __REC_UTIL_MESSAGEREGISTRARANDMAKER__
#define __REC_UTIL_MESSAGEREGISTRARANDMAKER__

#include <map>

#include "rec/util/proto/MessageMaker.h"
#include "rec/util/proto/MessageRegistrar.h"

namespace rec {
namespace util {

class MessageRegistrarAndMaker : public MessageRegistrar, public MessageMaker {
 public:
  MessageRegistrarAndMaker() {}
  virtual ~MessageRegistrarAndMaker();

  virtual Message* makeMessage(const string& typeName);

  virtual void registerInstance(const Message& m, bool copy = true);

 private:
  class Entry;
  typedef std::map<string, Entry*> Registry;

  Registry registry_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(MessageRegistrarAndMaker);
};

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_MESSAGEREGISTRARANDMAKER__
