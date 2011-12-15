#ifndef __REC_DATA_MESSAGEMAKER__
#define __REC_DATA_MESSAGEMAKER__

#include "rec/base/base.h"

namespace rec {
namespace data {

class MessageMaker {
 public:
  MessageMaker() {}
  virtual ~MessageMaker() {}

  virtual Message* makeMessage(const string& typeName) = 0;
};

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_MESSAGEMAKER__
