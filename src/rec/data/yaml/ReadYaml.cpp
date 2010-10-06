#include <iostream>
#include <sstream>
#include <vector>

#include "rec/data/yaml/Internal.h"

namespace rec {
namespace yaml {

namespace {

void operator>>(const YAML::Node& node, Message* to);

string str(const YAML::Node& node) {
  return node.Read<string>();
}

void doRead(const YAML::Node& n, Message* m, const FieldDescriptor* f) {
  const Reflection& r = *m->GetReflection();

  switch (f->type()) {
  case FD::TYPE_DOUBLE:   r.SetDouble(m, f, double(n)); break;
  case FD::TYPE_FLOAT:    r.SetFloat(m, f, float(n));   break;
  case FD::TYPE_INT64:    r.SetInt64(m, f, int64(n));   break;
  case FD::TYPE_UINT64:   r.SetUInt64(m, f, uint64(n)); break;
  case FD::TYPE_INT32:    r.SetInt32(m, f, int32(n));   break;
  case FD::TYPE_FIXED64:  r.SetUInt64(m, f, uint64(n)); break;
  case FD::TYPE_FIXED32:  r.SetUInt32(m, f, uint32(n)); break;
  case FD::TYPE_BOOL:     r.SetBool(m, f, bool(n));     break;
  case FD::TYPE_STRING:   r.SetString(m, f, str(n));    break;
  case FD::TYPE_UINT32:   r.SetUInt32(m, f, uint32(n)); break;
  case FD::TYPE_SFIXED32: r.SetInt32(m, f, int32(n));   break;
  case FD::TYPE_SFIXED64: r.SetInt64(m, f, int64(n));   break;
  case FD::TYPE_SINT32:   r.SetInt32(m, f, int32(n));   break;
  case FD::TYPE_SINT64:   r.SetInt64(m, f, int64(n));   break;
  case FD::TYPE_GROUP:    n >> r.MutableMessage(m, f);  break;
  case FD::TYPE_MESSAGE:  n >> r.MutableMessage(m, f);  break;
  case FD::TYPE_BYTES:    r.SetString(m, f, str(n));    break;
  case FD::TYPE_ENUM:
    r.SetEnum(m, f, f->enum_type()->FindValueByName(str(n)));
    break;
  default: LOG(ERROR) << "Didn't understand type " << f->type(); break; }
}

void doReadRepeated(const YAML::Node& node, Message* m, const FieldDescriptor* f) {
  const Reflection& r = *m->GetReflection();

  for (int i = 0; i < node.size(); ++i) {
    const YAML::Node& n = node[i];
    switch (f->type()) {
    case FD::TYPE_DOUBLE: r.AddDouble(m, f, double(n));  break;
    case FD::TYPE_FLOAT: r.AddFloat(m, f, float(n));     break;
    case FD::TYPE_INT64: r.AddInt64(m, f, int64(n));     break;
    case FD::TYPE_UINT64: r.AddUInt64(m, f, uint64(n));  break;
    case FD::TYPE_INT32: r.AddInt32(m, f, int32(n));     break;
    case FD::TYPE_FIXED64: r.AddUInt64(m, f, uint64(n)); break;
    case FD::TYPE_FIXED32: r.AddUInt32(m, f, uint32(n)); break;
    case FD::TYPE_BOOL: r.AddBool(m, f, bool(n));        break;
    case FD::TYPE_STRING: r.AddString(m, f, str(n));     break;
    case FD::TYPE_UINT32: r.AddUInt64(m, f, uint32(n));  break;
    case FD::TYPE_SFIXED32: r.AddInt32(m, f, int32(n));  break;
    case FD::TYPE_SFIXED64: r.AddInt64(m, f, int64(n));  break;
    case FD::TYPE_SINT32: r.AddInt32(m, f, int32(n));    break;
    case FD::TYPE_SINT64: r.AddInt64(m, f, int64(n));    break;
    case FD::TYPE_GROUP: n >> r.AddMessage(m, f);        break;
    case FD::TYPE_MESSAGE: n >> r.AddMessage(m, f);      break;
    case FD::TYPE_BYTES: r.AddString(m, f, str(n));      break;
    case FD::TYPE_ENUM:
      r.AddEnum(m, f, f->enum_type()->FindValueByName(str(n)));
      break;
    default:
      LOG(ERROR) << "Didn't understand type " << f->type(); break;
    }
  }
}

void operator>>(const YAML::Node& node, Message* to) {
  for (YAML::Iterator i = node.begin(); i != node.end(); ++i) {
    string name = str(i.first());
    if (const FieldDescriptor* f = to->GetDescriptor()->FindFieldByName(name)) {
      if (f->label() == FieldDescriptor::LABEL_REPEATED)
        doReadRepeated(i.second(), to, f);
      else
        doRead(i.second(), to, f);
    } else {
      LOG(ERROR) << "Couldn't understand field named " << name;
    }
  }
}

}  // namespace

void read(const string& from, Message* to) {
  std::istringstream s(from);
  YAML::Parser parser(s);

  YAML::Node node;
  if (!parser.GetNextDocument(node)) {
    LOG(ERROR) << "Didn't get any data";
    return;
  }

  node >> to;

  if (parser.GetNextDocument(node))
    LOG(ERROR) << "More than one document in file";
}

}  // namespace yaml
}  // namespace rec
