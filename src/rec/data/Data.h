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

class Data {
 public:
  virtual void operator()(OperationList*) = 0;
  virtual const Value getValue(const Address&) const = 0;
  virtual bool hasValue(const Address&) const = 0;
  virtual int getSize(const Address&) const = 0;
  virtual void copyTo(Message*) const = 0;

  Data() {}
  virtual ~Data() {}
};

void set(Data*, const Value& v);
void set(Data*, const Message& m);
void set(Data*, const Address&, const Value&);
void set(Data* d, const Address::Part& a, const Value& v);
void set(Data* d, const Address::Part& a,
         const Address::Part& b, const Value& v);


void append(Data*, const Value& v);
void append(Data*, const Message& m);
void append(Data*, const Address&, const Value& value);
void append(Data*, const Address::Part&, const Value& value);

#if 0
void clear(Data*, const Address&);
void remove(Data*, const Address&, int itemsToRemove);
void swap(Data*, const Address&, int index1, int index2);
#endif

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_DATA__
