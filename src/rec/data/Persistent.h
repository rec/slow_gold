#ifndef __REC_DATA_PERSISTENT__
#define __REC_DATA_PERSISTENT__

#include "rec/data/Data.h"

namespace rec {
namespace data {

class Persistent {
 public:
  virtual void operator()(OperationList*) = 0;
  virtual const Value getValue(const Address&) const = 0;
  virtual bool hasValue(const Address&) const = 0;
  virtual int getSize(const Address&) const = 0;
  virtual void copyTo(Message*) const = 0;

  Persistent() {}
  virtual ~Persistent() {}
};

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_PERSISTENT__
