#include <vector>
#include <glog/logging.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>

#include "rec/yaml/Yaml.h"
#include "rec/yaml/include/yaml.h"

namespace rec {
namespace yaml {

using google::protobuf::EnumValueDescriptor;
using google::protobuf::FieldDescriptor;
using google::protobuf::Reflection;

namespace {

YAML::Emitter& operator<<(YAML::Emitter& out, const Message& m);

YAML::Emitter& operator<<(YAML::Emitter& out, const EnumValueDescriptor* e) {
  return out << e->name();
}

struct MessageField {
  MessageField(const Message* m, const FieldDescriptor* f)
      : message_(m), field_(f) {
  }
  const Message* message_;
  const FieldDescriptor* field_;
};

struct MessageFieldIndex : public MessageField {
  MessageFieldIndex(const MessageField& mf, int i)
      : MessageField(mf), index_(i) {
  }
  int index_;
};

typedef FieldDescriptor FD;

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

typedef std::vector<const FieldDescriptor*> FieldVector;

YAML::Emitter& operator<<(YAML::Emitter& out, const Message& m) {
  out << YAML::BeginMap;

  FieldVector fields;
  m.GetReflection()->ListFields(m, &fields);

  for (FieldVector::const_iterator i = fields.begin(); i != fields.end(); ++i)
    out << YAML::Key << (*i)->name() << YAML::Value << MessageField(&m, *i);

  return out << YAML::EndMap;
}

}  // namespace


string write(const Message& from, bool compact) {
  YAML::Emitter out;
  out << from;
  return out.c_str();
}

}  // namespace yaml
}  // namespace rec



