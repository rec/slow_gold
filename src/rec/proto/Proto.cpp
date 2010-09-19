#include <glog/logging.h>

#include "rec/base/scoped_ptr.h"
#include "google/protobuf/descriptor.h"
#include "rec/proto/Proto.h"
#include "rec/proto/Field.h"

namespace rec {
namespace proto {

Operation* applyOperation(const Operation& operation,
                          google::protobuf::Message* msg) {
  return Field::apply(operation, msg);
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


#if 0
Operation* addTo(Operation* op, Tag tag) {
  op->add_address(tag);
  return op;}

Operation* make(Command command) {
  Operation* op = new Operation();
  op->set_command(command);
  return op;
}

Operation* make(Command c, uint32 t1) {
  return addTo(make(c), t1);
}

Operation* make(Command c, uint32 t1, uint32 t2) {
  return addTo(make(t1), t2);
}

Operation* make(Command c, uint32 t1, uint32 t2, uint32 t3) {
  return addTo(make(t1, t2), t3);
}

template <typename Item>

#define DEFINE_ADD(TYPE, UPPER)                             \
  template <> Operation* add(Operation* op, TYPE t) {       \
    return add(op, t, FieldDescriptor::TYPE_ ## UPPER);     \
  }

#define DEFINE_ADD_FIELD(TYPE)                                      \
  template <> Operation* add(Operation* op, TYPE t, FieldDescriptor::Type f) {  \
    return op; \
    Value* value = op->add_value()
  }

#define DEFINE_TYPE(TYPE, UPPER)                             \
  template <> FieldDescriptor::Type getFieldType<TYPE>() {               \
    return FieldDescriptor:::TYPE_ ## UPPER);                \
  }


template <typename Item>
void setValue(Value* v, FieldDescriptor* f, Item x);

template <>
void setValue(Value* v, FieldDescriptor* f, double x) {
  v->GetReflection()->SetDouble(v, f, x);
}

}

template <typename Item>
Operation* addValue(Operation* op, Item x, FieldDescriptor::Type type = GetType::TYPE) {
  FieldDescription* f = Value::GetDescriptor()->FindFieldByNumber(type);
  setValue(op->add_value(), Value::GetDescriptor()->FindFieldByNumber(type), x);
  return op;
}

template <>
Operation* add(Operation* op, Item item)

template <typename Item>
Operation* add(Operation* op, Item item, FieldDescriptor::Type type)


Operation* add(Operation* op, const Message& message) {
  message.SerializeToString(op->add_value()->mutable_message_f());
  return op;
}



Operation

Operation* newOperation(Operation::Command command, const IntList& list) {
  Operation *op = new Operation();
  op->set_command(command);

  for (IntList::const_iterator i = list.begin(); i != list.end(); ++i)
    op->add_address(*i);

  return op;

}

struct Field {
  const Operation* operation_;
  Message* message_;
  const FieldDescriptor* field_;
  uint32 index_;
  bool isIndexed_;

  const Descriptor& descriptor() const { return *(message_->GetDescriptor()); }
  const Reflection& reflection() const { return *(message_->GetReflection()); }

  Operation* apply(const Operation& op) {
    switch (op.command()) {
     case Operation::CLEAR:        return clear(op);
     case Operation::SET:          return set(op);
     case Operation::APPEND:       return append(op);
     case Operation::REMOVE_LAST:  return removeLast(op);
     case Operation::SWAP:         return swap(op);
     default: return NULL;
    }
  }

  Operation* clear(const Operation& op) {
    if (isIndexed_) {
      LOG(ERROR) << "Can't clear an indexed value";
      return NULL;
    }

    scoped_ptr<Operation> undo(new Operation());
    undo->set_command(Operation::SET);

    if (isRepeated()) {

    }


  Operation* apply(const Operation& op) {
    const Reflection& f = reflection();
    const bool repeated = isRepeated();

    Operation::Command c = op.command();
    if (c == Operation::SET) {
      int inSize = op.value_size();
      if (repeated) {
        Operation* undo = new Operation();
        undo->set_
        int outSize = r->FieldSize(message_, field_);
        for (int i = 0; i < outSize; ++i)
          copyTo(i, undo->add_value(i), field_, message_);

        r->ClearField(message_, field);
        for (int i = 0; i < inSize; ++i)
          copyFrom(undo->add_value(i)->CopyFrom(op.value(i)));

        return undo.transfer();

      } else if (inSize != 1) {
        LOG(ERROR) << "Setting just a single value, " << inSize;

      } else if (isIndexed_) {
        if (copyTo(index_, undo->mutable_value(0), field_, message_) &&
            copyFrom(index_, op.value(0), field_, message_))
          return undo.transfer();

      } else {
        if (copyTo(undo->mutable_value(0), field_, message_) &&
            copyFrom(op.value(0), field_, message_))
          return undo.transfer();

      }

      for (int i = 0; i <
        if (
        int originalSize =
        undo->clear_value();
        for (int i = 0; i < originalSize; ++i) {
          if (!copyTo(
        }

      } else if (inSize != 1) {
        LOG(ERROR) << "Non-repeated elements can only have a single value";
        return NULL;
      }

      for (int i = 0; i <

    }
    if (isIndexed_) {
      if (c != Operation::SET)
        LOG(ERROR) << "indexed elements can only be SET: " << c;

      else if (undo->value_size() != 1)
        LOG(ERROR) << "Indexed SET operations must have exactly 1 value " << c;

      else if (!copyTo(undo->mutable_value(0)))
        LOG(ERROR) << "Couldn't store undo value";

      else if (!copyFrom(op.value()))
        LOG(ERROR) << "Couldn't set value";

      else
        return undo.release();

    } else if (isRepeated()) {
      if (c == Operation::SET) {
        undo->clear_value();
        for (int i = 0; i < op.value_size(); ++i)

      if (c == Operation::CLEAR) {
        if (!copyTo(undo->mutable_value(0)))
          LOG(ERROR) << "Couldn't store undo value";


      } else if (c == Operation::CLEAR) {
      } else {
        LOG(ERROR) << "Single entries can only be set or cleared";
      }

    } else {
      if (c == Operation::SET) {
      } else if (c == Operation::CLEAR) {
      } else {
        LOG(ERROR) << "Single entries can only be set or cleared";
      }
    }
    return NULL;
  }

  bool clear(Operation* operation) {
    if (isIndexed_) {
      LOG(ERROR) << "Can't clear indexed items";
      return false;
    }
    return true;
  }
};




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

  bool checkField() {
    Operation::Command c = operation_.command();
    bool hasValue = false;
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
     case Operation::APPEND:       return append();
     case Operation::CLEAR:        return clear();
     case Operation::REMOVE_LAST:  return removeLast();
     case Operation::SET:          return set();
     case Operation::SWAP:         return swap();
     default:                      return false;
    }
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
      // PR_CASE(group, Group, GROUP)
      PR_CASE(bytes, String, BYTES)
      PR_CASE(uint32, UInt32, UINT32)
      // PR_CASE(enum, Enum, ENUM)
      PR_CASE(sfixed32, UInt32, SFIXED32)
      PR_CASE(sfixed64, UInt64, SFIXED64)
      PR_CASE(sint32, Int32, SINT32)
      PR_CASE(sint64, Int64, SINT64)

    case FieldDescriptor::TYPE_MESSAGE:
       return r->AddMessage(message_, field_)->ParseFromString(v.message_f());

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

  bool removeLast() {
    message_->GetReflection()->RemoveLast(message_, field_);
    return true;
  }

  bool set() {
    const Reflection* r = message_->GetReflection();
    const Value& v = operation_.value();
    switch (field_->type()) {
  #define PR_CASE(TYPE, TYPE_CAP, TYPE_UPPER) \
      case FieldDescriptor::TYPE_ ## TYPE_UPPER: \
       if (isIndexed_)\
         r->SetRepeated##TYPE_CAP(message_, field_, index_, v.TYPE ## _f());\
       else\
         r->Set ## TYPE_CAP(message_, field_, v.TYPE ## _f()); \
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

    case FieldDescriptor::TYPE_MESSAGE:
       return r->MutableMessage(message_, field_)->
         ParseFromString(v.message_f());

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

std::ostream& operator<<(std::ostream& os, const Applier& a) {
  return os << "applier("
            << a.operation().command() << ", "
            << a.operation().command() << ", "
}


}  // namespace


bool applyOperation(const Operation& operation,
                    google::protobuf::Message* msg) {
  scoped_ptr<Applier> applier(createApplier(operation, msg));
  return applier && applier->apply();
}
#endif

}  // namespace proto
}  // namespace rec
