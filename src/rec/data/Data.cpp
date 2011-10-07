#include "rec/data/Address.h"
#include "rec/data/Data.h"
#include "rec/data/Value.h"
#include "rec/data/Operation.pb.h"

namespace rec {
namespace data {

namespace {

typedef Operation::Command Command;

Operation* newOp(Command c, const Address& a) {
  Operation* op = new Operation();
  op->set_command(c);
  op->mutable_address()->CopyFrom(a);
  return op;
}

Operation* valueOp(Command c, const Address& a, const Value& value) {
  Operation* op = newOp(c, a);
  op->add_value()->CopyFrom(value);
  return op;
}

Operation* removeOp(const Address& a, int remove) {
  Operation* op = newOp(Operation::REMOVE, a);
  op->set_remove(remove);
  return op;
}

Operation* swapOp(const Address& a, int s, int t) {
  Operation* op = newOp(Operation::SWAP, a);
  op->set_swap1(s);
  op->set_swap2(t);
  return op;
}

void setOp(EditableData* setter, Operation* oper) {
  ptr<Operation> op(oper);
  ptr<OperationList> list(new OperationList);
  list->add_operation()->CopyFrom(*op);
  (*setter)(list.transfer());
}


}  // namespace

void append(EditableData* data, const Address& address, const Value& value) {
  setOp(data, valueOp(Operation::APPEND, address, value));
}

void clear(EditableData* data, const Address& address) {
  setOp(data, newOp(Operation::CLEAR, address));
}

void remove(EditableData* data, const Address& address, int remove) {
  setOp(data, removeOp(address, remove));
}

void set(EditableData* data, const Address& address, const Value& value) {
  setOp(data, valueOp(Operation::SET, address, value));
}

void swap(EditableData* data, const Address& a, int s, int t) {
  setOp(data, swapOp(a, s, t));
}

void append(EditableData* d, const Value& v) { append(d, Address(), v); }
void append(EditableData* d, const Message& m) { append(d, Address(), Value(m)); }
void append(EditableData* d, const Address::Part& a, const Value& m) {
  append(d, Address(a), m);
}

void set(EditableData* d, const Value& v) { set(d, Address(), v); }
void set(EditableData* d, const Message& m) { set(d, Address(), Value(m)); }

void set(EditableData* d, const Address::Part& a, const Value& v) {
  set(d, Address(a), v);
}

void set(EditableData* d, const Address::Part& a,
         const Address::Part& b, const Value& v) {
  set(d, Address(a, b), v);
}

#if 0

void append(const Address::Part& a, const Value& v) { append(Address(a), v); }
void append(const Address::Part& a, const Address::Part& b, const Value& v) { append(Address(a, b), v); }
void append(const Address::Part& a, const Address::Part& b, const Address::Part& c, const Value& v) { append(Address(a, b, c), v); }
void append(const Address::Part& a, const Address::Part& b, const Address::Part& c, const Address::Part& d, const Value& v) { append(Address(a, b, c, d), v); }
void append(const Address::Part& a, const Address::Part& b, const Address::Part& c, const Address::Part& d, const Address::Part& e, const Value& v) { append(Address(a, b, c, d, e), v); }

void append(const Address::Part& a, const Message& m) { append(Address(a), Value(m)); }
void append(const Address::Part& a, const Address::Part& b, const Message& m) { append(Address(a, b), Value(m)); }
void append(const Address::Part& a, const Address::Part& b, const Address::Part& c, const Message& m) { append(Address(a, b, c), Value(m)); }
void append(const Address::Part& a, const Address::Part& b, const Address::Part& c, const Address::Part& d, const Message& m) { append(Address(a, b, c, d), Value(m)); }
void append(const Address::Part& a, const Address::Part& b, const Address::Part& c, const Address::Part& d, const Address::Part& e, const Message& m) { append(Address(a, b, c, d, e), Value(m)); }

void clear() { clear(Address()); }
void clear(const Address::Part& a) { clear(Address(a)); }
void clear(const Address::Part& a, const Address::Part& b) { clear(Address(a, b)); }
void clear(const Address::Part& a, const Address::Part& b, const Address::Part& c) { clear(Address(a, b, c)); }
void clear(const Address::Part& a, const Address::Part& b, const Address::Part& c, const Address::Part& d) { clear(Address(a, b, c, d)); }
void clear(const Address::Part& a, const Address::Part& b, const Address::Part& c, const Address::Part& d, const Address::Part& e) { clear(Address(a, b, c, d, e)); }

void remove(int i)  { remove(Address(), i); }
void remove(const Address::Part& a, int i)  { remove(Address(a), i); }
void remove(const Address::Part& a, const Address::Part& b, int i)  { remove(Address(a, b), i); }
void remove(const Address::Part& a, const Address::Part& b, const Address::Part& c, int i)  { remove(Address(a, b, c), i); }
void remove(const Address::Part& a, const Address::Part& b, const Address::Part& c, const Address::Part& d, int i)  { remove(Address(a, b, c, d), i); }
void remove(const Address::Part& a, const Address::Part& b, const Address::Part& c, const Address::Part& d, const Address::Part& e, int i)  { remove(Address(a, b, c, d, e), i); }

void set(const Address::Part& a, const Value& v) { set(Address(a), v); }
void set(const Address::Part& a, const Address::Part& b, const Value& v) { set(Address(a, b), v); }
void set(const Address::Part& a, const Address::Part& b, const Address::Part& c, const Value& v) { set(Address(a, b, c), v); }
void set(const Address::Part& a, const Address::Part& b, const Address::Part& c, const Address::Part& d, const Value& v) { set(Address(a, b, c, d), v); }
void set(const Address::Part& a, const Address::Part& b, const Address::Part& c, const Address::Part& d, const Address::Part& e, const Value& v) { set(Address(a, b, c, d, e), v); }

void set(const Address::Part& a, const Message& m) { set(Address(a), Value(m)); }
void set(const Address::Part& a, const Address::Part& b, const Message& m) { set(Address(a, b), Value(m)); }
void set(const Address::Part& a, const Address::Part& b, const Address::Part& c, const Message& m) { set(Address(a, b, c), Value(m)); }
void set(const Address::Part& a, const Address::Part& b, const Address::Part& c, const Address::Part& d, const Message& m) { set(Address(a, b, c, d), Value(m)); }
void set(const Address::Part& a, const Address::Part& b, const Address::Part& c, const Address::Part& d, const Address::Part& e, const Message& m) { set(Address(a, b, c, d, e), Value(m)); }

void swap(int s, int t) { swap(Address(), s, t); }
void swap(const Address::Part& a, int s, int t) { swap(Address(a), s, t); }
void swap(const Address::Part& a, const Address::Part& b, int s, int t) { swap(Address(a, b), s, t); }
void swap(const Address::Part& a, const Address::Part& b, const Address::Part& c, int s, int t) { swap(Address(a, b, c), s, t); }
void swap(const Address::Part& a, const Address::Part& b, const Address::Part& c, const Address::Part& d, int s, int t) { swap(Address(a, b, c, d), s, t); }
void swap(const Address::Part& a, const Address::Part& b, const Address::Part& c, const Address::Part& d, const Address::Part& e, int s, int t) { swap(Address(a, b, c, d, e), s, t); }

const Value getValue() const { return getValue(Address()); }
const Value getValue(const Address::Part& a) const { return getValue(Address(a)); }
const Value getValue(const Address::Part& a, const Address::Part& b) const { return getValue(Address(a, b)); }
const Value getValue(const Address::Part& a, const Address::Part& b, const Address::Part& c) const { return getValue(Address(a, b, c)); }
const Value getValue(const Address::Part& a, const Address::Part& b, const Address::Part& c, const Address::Part& d) const { return getValue(Address(a, b, c, d)); }
const Value getValue(const Address::Part& a, const Address::Part& b, const Address::Part& c, const Address::Part& d, const Address::Part& e) const { return getValue(Address(a, b, c, d, e)); }

bool hasValue() const { return hasValue(Address()); }
bool hasValue(const Address::Part& a) const { return hasValue(Address(a)); }
bool hasValue(const Address::Part& a, const Address::Part& b) const { return hasValue(Address(a, b)); }
bool hasValue(const Address::Part& a, const Address::Part& b, const Address::Part& c) const { return hasValue(Address(a, b, c)); }
bool hasValue(const Address::Part& a, const Address::Part& b, const Address::Part& c, const Address::Part& d) const { return hasValue(Address(a, b, c, d)); }
bool hasValue(const Address::Part& a, const Address::Part& b, const Address::Part& c, const Address::Part& d, const Address::Part& e) const { return hasValue(Address(a, b, c, d, e)); }
#endif

}  // namespace data
}  // namespace rec

