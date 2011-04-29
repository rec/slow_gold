#include "rec/data/proto/Setter.h"

namespace rec {
namespace proto {
namespace arg {

void Setter::operator()(Operation* oper) {
  ptr<Operation> op(oper);
  ptr<OperationList> list(new OperationList);
  list->add_operation()->CopyFrom(*op);
  (*this)(list.transfer());
}

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

}  // namespace

void Setter::append(const Address& address, const Value& value) {
  (*this)(valueOp(Operation::APPEND, address, value));
}

void Setter::clear(const Address& address) {
  (*this)(newOp(Operation::CLEAR, address));
}

void Setter::remove(const Address& address, int remove) {
  (*this)(removeOp(address, remove));
}

void Setter::set(const Address& address, const Value& value) {
  (*this)(valueOp(Operation::SET, address, value));
}

void Setter::swap(const Address& a, int s, int t) {
  (*this)(swapOp(a, s, t));
}

}  // namespace arg
}  // namespace proto
}  // namespace rec
