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

  virtual void apply(OperationList*) = 0;

  virtual const Value getValue(const Address&) const = 0;
  virtual bool hasValue(const Address&) const = 0;
  virtual int getSize(const Address&) const = 0;
  virtual void copyTo(Message*) const = 0;
};

void set(Editable*, const Value& v);
void set(Editable*, const Message& m);
void set(Editable*, const Address&, const Value&);
void set(Editable* d, const Address::Part& a, const Value& v);
void set(Editable* d, const Address::Part& a,
         const Address::Part& b, const Value& v);

void append(Editable*, const Value& v);
void append(Editable*, const Message& m);
void append(Editable*, const Address&, const Value& value);
void append(Editable*, const Address::Part&, const Value& value);

#if 0
void clear(Editable*, const Address&);
void remove(Editable*, const Address&, int itemsToRemove);
void swap(Editable*, const Address&, int index1, int index2);
#endif

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_EDITABLE__
