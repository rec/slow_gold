#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>

#include "rec/data/yaml/Internal.h"

namespace rec {
namespace yaml {
namespace {

YAML::Emitter& operator<<(YAML::Emitter& out, const Message& m);

YAML::Emitter& operator<<(YAML::Emitter& out, const EnumValueDescriptor* e) {
  return out << e->name();
}

YAML::Emitter& operator<<(YAML::Emitter& out, const MessageFieldIndex& mfi) {
  const Message& m = *mfi.message_;
  const FieldDescriptor* f = mfi.field_;
  int i = mfi.index_;
  const Reflection& r = *m.GetReflection();
  switch (f->type()) {
   case FD::TYPE_DOUBLE:   return out << r.GetRepeatedDouble(m, f, i);
   case FD::TYPE_FLOAT:    return out << r.GetRepeatedFloat(m, f, i);
   case FD::TYPE_INT64:    return out << r.GetRepeatedInt64(m, f, i);
   case FD::TYPE_UINT64:   return out << r.GetRepeatedUInt64(m, f, i);
   case FD::TYPE_INT32:    return out << r.GetRepeatedInt32(m, f, i);
   case FD::TYPE_FIXED64:  return out << r.GetRepeatedUInt64(m, f, i);
   case FD::TYPE_FIXED32:  return out << r.GetRepeatedUInt32(m, f, i);
   case FD::TYPE_BOOL:     return out << r.GetRepeatedBool(m, f, i);
   case FD::TYPE_STRING:   return out << r.GetRepeatedString(m, f, i);
   case FD::TYPE_UINT32:   return out << r.GetRepeatedUInt32(m, f, i);
   case FD::TYPE_SFIXED32: return out << r.GetRepeatedInt32(m, f, i);
   case FD::TYPE_SFIXED64: return out << r.GetRepeatedInt64(m, f, i);
   case FD::TYPE_SINT32:   return out << r.GetRepeatedInt32(m, f, i);
   case FD::TYPE_SINT64:   return out << r.GetRepeatedInt64(m, f, i);
   case FD::TYPE_GROUP:    return out << r.GetRepeatedMessage(m, f, i);
   case FD::TYPE_MESSAGE:  return out << r.GetRepeatedMessage(m, f, i);
   case FD::TYPE_BYTES:    return out << r.GetRepeatedString(m, f, i);
   case FD::TYPE_ENUM:     return out << r.GetRepeatedEnum(m, f, i);
   default: LOG(ERROR) << "Didn't understand type " << f->type(); return out;
  }
}

YAML::Emitter& operator<<(YAML::Emitter& out, const MessageField& mf) {
  const Message& m = *mf.message_;
  const FieldDescriptor* f = mf.field_;
  const Reflection& r = *m.GetReflection();

  if (f->label() == FD::LABEL_REPEATED) {
    out << YAML::BeginSeq;
    for (int i = 0; i < r.FieldSize(m, f); ++i) {
      out << MessageFieldIndex(mf, i);
    }
    return out << YAML::EndSeq;
  }

  switch (f->type()) {
   case FD::TYPE_DOUBLE:   return out << r.GetDouble(m, f);
   case FD::TYPE_FLOAT:    return out << r.GetFloat(m, f);
   case FD::TYPE_INT64:    return out << r.GetInt64(m, f);
   case FD::TYPE_UINT64:   return out << r.GetUInt64(m, f);
   case FD::TYPE_INT32:    return out << r.GetInt32(m, f);
   case FD::TYPE_FIXED64:  return out << r.GetUInt64(m, f);
   case FD::TYPE_FIXED32:  return out << r.GetUInt32(m, f);
   case FD::TYPE_BOOL:     return out << r.GetBool(m, f);
   case FD::TYPE_STRING:   return out << r.GetString(m, f);
   case FD::TYPE_UINT32:   return out << r.GetUInt32(m, f);
   case FD::TYPE_SFIXED32: return out << r.GetInt32(m, f);
   case FD::TYPE_SFIXED64: return out << r.GetInt64(m, f);
   case FD::TYPE_SINT32:   return out << r.GetInt32(m, f);
   case FD::TYPE_SINT64:   return out << r.GetInt64(m, f);
   case FD::TYPE_GROUP:    return out << r.GetMessage(m, f);
   case FD::TYPE_MESSAGE:  return out << r.GetMessage(m, f);
   case FD::TYPE_BYTES:    return out << r.GetString(m, f);
   case FD::TYPE_ENUM:     return out << r.GetEnum(m, f);
   default: LOG(ERROR) << "Didn't understand type " << f->type(); return out;
  }
}

typedef vector<const FieldDescriptor*> FieldVector;

#ifdef SHOULD_REMOVE
static const unsigned int MAX_FIELD_COUNT = 5;
static const int MAX_ARRAY_COUNT = 8;

bool isSmall(const Message& m) {
  FieldVector fields;
  m.GetReflection()->ListFields(m, &fields);

  if (fields.size() > MAX_FIELD_COUNT)
    return false;

  for (FieldVector::const_iterator i = fields.begin(); i != fields.end(); ++i) {
    if ((*i)->label() == FieldDescriptor::LABEL_REPEATED ||
        (*i)->type() == FieldDescriptor::TYPE_GROUP ||
        (*i)->type() == FieldDescriptor::TYPE_MESSAGE)
      return false;
  }
  return true;
}
#endif

YAML::Emitter& write(YAML::Emitter& out, const Message& m) {
  FieldVector fields;
  m.GetReflection()->ListFields(m, &fields);

  out << YAML::BeginMap;
  for (FieldVector::const_iterator i = fields.begin(); i != fields.end(); ++i)
    out << YAML::Key << (*i)->name() << YAML::Value << MessageField(&m, *i);

  out << YAML::EndMap;
  return out;
}

int shortLength(const Message &m) {
  YAML::Emitter out;
  out << YAML::Flow;
  write(out, m);
  return strlen(out.c_str());
}

const static int SHORT_LENGTH = 80;

YAML::Emitter& operator<<(YAML::Emitter& out, const Message& m) {
  bool small = (shortLength(m) < SHORT_LENGTH);
  out << (small ? YAML::Flow : YAML::Block) << YAML::BeginMap;

  FieldVector fields;
  m.GetReflection()->ListFields(m, &fields);

  for (FieldVector::const_iterator i = fields.begin(); i != fields.end(); ++i)
    out << YAML::Key << (*i)->name() << YAML::Value << MessageField(&m, *i);

  out << YAML::EndMap << YAML::Block;

  return out;
}

}  // namespace

string write(const Message& from) {
  YAML::Emitter out;

  out << YAML::BeginMap;
  out << YAML::Key << "type" << YAML::Value << from.GetTypeName();
  out << YAML::Key << "value" << YAML::Value << from;
  out << YAML::EndMap;
  return out.c_str();
}

}  // namespace yaml
}  // namespace rec



