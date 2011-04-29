#ifndef __REC_DATA_OPERABLE__
#define __REC_DATA_OPERABLE__

#include "rec/data/Data.h"

namespace rec {
namespace data {

class Operable {
 public:
  virtual void operator()(OperationList*) = 0;
  virtual const Value getValue(const Address&) const = 0;
  virtual bool hasValue(const Address&) const = 0;
  virtual int getSize(const Address&) const = 0;
  virtual void copyTo(Message*) const = 0;

  Operable() {}
  virtual ~Operable() {}
};

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_OPERABLE__
