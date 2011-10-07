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

class EditableData {
 public:
  virtual void operator()(OperationList*) = 0;

  virtual const Value getValue(const Address&) const = 0;
  virtual bool hasValue(const Address&) const = 0;
  virtual int getSize(const Address&) const = 0;
  virtual void copyTo(Message*) const = 0;

  EditableData() {}
  virtual ~EditableData() {}
};

void set(EditableData*, const Value& v);
void set(EditableData*, const Message& m);
void set(EditableData*, const Address&, const Value&);
void set(EditableData* d, const Address::Part& a, const Value& v);
void set(EditableData* d, const Address::Part& a,
         const Address::Part& b, const Value& v);

void append(EditableData*, const Value& v);
void append(EditableData*, const Message& m);
void append(EditableData*, const Address&, const Value& value);
void append(EditableData*, const Address::Part&, const Value& value);

#if 0
void clear(EditableData*, const Address&);
void remove(EditableData*, const Address&, int itemsToRemove);
void swap(EditableData*, const Address&, int index1, int index2);
#endif

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_DATA__
