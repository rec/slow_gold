#include <glog/logging.h>

#include "rec/base/scoped_ptr.h"
#include "google/protobuf/descriptor.h"
#include "rec/proto/Proto.h"

using google::protobuf::Descriptor;
using google::protobuf::FieldDescriptor;
using google::protobuf::Reflection;
using google::protobuf::Message;

namespace rec {
namespace proto {

namespace {

class Applier {
 public:
  Applier(const Operation& op, Message* msg, const FieldDescriptor* f)
      : operation_(op),
        message_(msg),
        field_(f),
        index_(-1),
        isIndexed_(false) {
  }

  Applier(int index, const Operation& op, Message* msg, const FieldDescriptor* f)
    : operation_(op),
      message_(msg),
      field_(f),
      index_(index),
      isIndexed_(true) {
  }

  static Applier* create(const Operation& op, Message* msg);

  bool checkField() {
    Operation::Command c = operation_.command();

    const Value& v = operation_.value();
    const Descriptor* desc = v.GetDescriptor();
    const FieldDescriptor *f = desc->FindFieldByNumber(field_->type());

    bool hasValue = f && v.GetReflection()->HasField(v, f);
    bool needsValue = c == Operation::SET || c == Operation::APPEND;
    if (needsValue != hasValue) {
      LOG(ERROR) << c << " takes " << (needsValue ? "a" : "no") << " value."
                 << field_->type();
      return false;
    }

    if (c != Operation::CLEAR) {
      bool needsRepeat =
        c == Operation::ADD ||
        c == Operation::APPEND ||
        c == Operation::REMOVE_LAST ||
        c == Operation::SWAP;

      bool hasRepeat = !isIndexed_ &&
        (field_->label() == FieldDescriptor::LABEL_REPEATED);

      if (needsRepeat != hasRepeat) {
        LOG(ERROR) << c << " needs " << (hasRepeat ? "" : "un") <<  "repeat";
        return false;
      }
    }


    return true;
  }

  bool apply() {
    if (!checkField())
      return false;

    switch (operation_.command()) {
     case Operation::ADD:          return add();
     case Operation::APPEND:       return append();
     case Operation::CLEAR:        return clear();
     case Operation::CREATE:       return create();
     case Operation::REMOVE_LAST:  return removeLast();
     case Operation::SET:          return set();
     case Operation::SWAP:         return swap();
     default:                      return false;
    }
  }

  bool add() {
    if (field_->type() == FieldDescriptor::TYPE_MESSAGE)
      return message_->GetReflection()->AddMessage(message_, field_);

    LOG(ERROR) << "Can only add Messages";
    return false;
  }

  bool append() {
    const Reflection* r = message_->GetReflection();
  #define PR_CASE(TYPE, TYPE_CAP, TYPE_UPPER) \
    case FieldDescriptor::TYPE_ ## TYPE_UPPER:                     \
       r->Add ## TYPE_CAP(message_, field_, operation_.value().TYPE ## _f());  \
       return true;

    switch (field_->type()) {
      PR_CASE(double, Double, DOUBLE)
      PR_CASE(float, Float, FLOAT)
      PR_CASE(int64, Int64, INT64)
      PR_CASE(uint64, UInt64, UINT64)
      PR_CASE(int32, Int32, INT32)
      PR_CASE(fixed64, UInt64, FIXED64)
      PR_CASE(fixed32, UInt32, FIXED32)
      PR_CASE(bool, Bool, BOOL)
      PR_CASE(string, String, STRING)
      // PR_CASE(message, Message, MESSAGE)  already done
      // PR_CASE(group, Group, GROUP)
      PR_CASE(bytes, String, BYTES)
      PR_CASE(uint32, UInt32, UINT32)
      // PR_CASE(enum, Enum, ENUM)
      PR_CASE(sfixed32, UInt32, SFIXED32)
      PR_CASE(sfixed64, UInt64, SFIXED64)
      PR_CASE(sint32, Int32, SINT32)
      PR_CASE(sint64, Int64, SINT64)

     default:
      LOG(ERROR) << "Didn't understand type " << field_->type();
      return false;
    }
  #undef PR_CASE
  }

  bool clear() {
    if (isIndexed_)
      LOG(ERROR) << "Cannot clear indexed values";
    else
      message_->GetReflection()->ClearField(message_, field_);

    return !isIndexed_;
  }

  bool create() {
    const Reflection* r = message_->GetReflection();
    return !r->HasField(*message_, field_) &&
      r->MutableMessage(message_, field_);
  }

  bool removeLast() {
    message_->GetReflection()->RemoveLast(message_, field_);
    return true;
  }

  bool set() {
    const Reflection* r = message_->GetReflection();

    switch (field_->type()) {
  #define PR_CASE(TYPE, TYPE_CAP, TYPE_UPPER) \
      case FieldDescriptor::TYPE_ ## TYPE_UPPER: \
       if (isIndexed_)\
         r->SetRepeated##TYPE_CAP(message_, field_, index_, operation_.value().TYPE ## _f());\
       else\
         r->Set ## TYPE_CAP(message_, field_, operation_.value().TYPE ## _f()); \
       return true;

      PR_CASE(double, Double, DOUBLE)
      PR_CASE(float, Float, FLOAT)
      PR_CASE(int64, Int64, INT64)
      PR_CASE(uint64, UInt64, UINT64)
      PR_CASE(int32, Int32, INT32)
      PR_CASE(fixed64, UInt64, FIXED64)
      PR_CASE(fixed32, UInt32, FIXED32)
      PR_CASE(bool, Bool, BOOL)
      PR_CASE(string, String, STRING)
      // PR_CASE(message, Message, MESSAGE)  We'd need to serialize.
      // PR_CASE(group, Group, GROUP)
      PR_CASE(bytes, String, BYTES)
      PR_CASE(uint32, UInt32, UINT32)
      // PR_CASE(enum, Enum, ENUM)
      PR_CASE(sfixed32, UInt32, SFIXED32)
      PR_CASE(sfixed64, UInt64, SFIXED64)
      PR_CASE(sint32, Int32, SINT32)
      PR_CASE(sint64, Int64, SINT64)

     default:
      LOG(ERROR) << "Didn't understand type " << field_->type();
      return false;
    }

  #undef PR_CASE
  }

  bool swap() {
    message_->GetReflection()->SwapElements(message_, field_,
                                            operation_.swap1(),
                                            operation_.swap2());
    return true;
  }

  friend std::ostream& operator<<(std::ostream& os, const Applier& applier);

  const Operation& operation_;
  Message* const message_;
  const FieldDescriptor* const field_;
  const int index_;
  const bool isIndexed_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Applier);
};

Applier* createApplier(const Operation& op, Message* msg) {
  for (int i = 0; i < op.address_size(); ++i) {
    const Descriptor* desc = msg->GetDescriptor();
    uint32 index = op.address(i);
    const FieldDescriptor* field = desc->FindFieldByNumber(index);

    if (!field) {
      LOG(ERROR) << "No submessage with i=" << i << ", index=" << index;
      return NULL;
    }

    if (i == op.address_size() - 1)
      return new Applier(op, msg, field);

    bool is_message = field->type() == FieldDescriptor::TYPE_MESSAGE;
    bool is_repeated = field->label() == FieldDescriptor::LABEL_REPEATED;

    if (is_repeated && i == op.address_size() - 2)
      return new Applier(op.address(++i), op, msg, field);

    if (!is_message) {
      LOG(ERROR) << "Non-terminal field had non-message type "
                 << field->type();
      return NULL;
    }

    const Reflection* reflection = msg->GetReflection();
    if (is_repeated)
      msg = reflection->MutableRepeatedMessage(msg, field, op.address(++i));
    else
      msg = reflection->MutableMessage(msg, field);
  }

  LOG_FIRST_N(ERROR, 1) << "Empty address";
  return NULL;
}

#if 0
std::ostream& operator<<(std::ostream& os, const Applier& a) {
  return os << "applier("
            << a.operation().command() << ", "
            << a.operation().command() << ", "
}

#endif

}  // namespace

bool applyOperation(const Operation& operation,
                    google::protobuf::Message* msg) {
  scoped_ptr<Applier> applier(createApplier(operation, msg));
  return applier && applier->apply();
}

Operation* createOperation(Operation::Command command, ...) {
  Operation *op = new Operation();
  op->set_command(command);

  va_list ap;
  va_start(ap, command);

  for (uint32 addr = va_arg(ap, uint32); addr; addr = va_arg(ap, uint32))
    op->add_address(addr);

  return op;
}

}  // namespace proto
}  // namespace rec
