#ifndef __REC_DATA_MESSAGEREGISTRARANDMAKER__
#define __REC_DATA_MESSAGEREGISTRARANDMAKER__

#include <map>

#include "rec/data/MessageMaker.h"
#include "rec/data/MessageRegistrar.h"

namespace rec {
namespace data {

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

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_MESSAGEREGISTRARANDMAKER__
