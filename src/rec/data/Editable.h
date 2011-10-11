#ifndef __REC_DATA_EDITABLE__
#define __REC_DATA_EDITABLE__

#include "rec/base/base.h"
#include "rec/data/Address.h"

namespace rec {
namespace data {

class Address;
class AddressProto;
class Operation;
class OperationList;
class Value;
class ValueProto;

class Editable {
 public:
  Editable() {}
  virtual ~Editable() {}

  void set(const Value&, const Address& a = Address::default_instance());
  void append(const Value& value, const Address&);

  virtual void apply(OperationList*) = 0;

  virtual const Value getValue(const Address&) const = 0;
  virtual bool hasValue(const Address&) const = 0;
  virtual int getSize(const Address&) const = 0;
  virtual void copyTo(Message*) const = 0;
};

// There are more setters in archived/OldEditable.h

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_EDITABLE__
