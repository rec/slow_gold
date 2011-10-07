#ifndef __REC_DATA_DATA__
#define __REC_DATA_DATA__

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
  data::Editable() {}
  virtual ~data::Editable() {}

  virtual void operator()(OperationList*) = 0;

  virtual const Value getValue(const Address&) const = 0;
  virtual bool hasValue(const Address&) const = 0;
  virtual int getSize(const Address&) const = 0;
  virtual void copyTo(Message*) const = 0;
};

void set(data::Editable*, const Value& v);
void set(data::Editable*, const Message& m);
void set(data::Editable*, const Address&, const Value&);
void set(data::Editable* d, const Address::Part& a, const Value& v);
void set(data::Editable* d, const Address::Part& a,
         const Address::Part& b, const Value& v);

void append(data::Editable*, const Value& v);
void append(data::Editable*, const Message& m);
void append(data::Editable*, const Address&, const Value& value);
void append(data::Editable*, const Address::Part&, const Value& value);

#if 0
void clear(data::Editable*, const Address&);
void remove(data::Editable*, const Address&, int itemsToRemove);
void swap(data::Editable*, const Address&, int index1, int index2);
#endif

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_DATA__
