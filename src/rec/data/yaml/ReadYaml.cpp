#include <iostream>
#include <sstream>

#include "rec/data/yaml/Internal.h"

#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.h>

namespace rec {
namespace yaml {

namespace {

void read(const YAML::Node& node, Message* to);

string str(const YAML::Node& node) {
    return node.Read<string>();
}

using FD = google::protobuf::FieldDescriptor;

void read(const YAML::Node& n, Message* m, const FieldDescriptor* f) {
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
    case FD::TYPE_GROUP:    read(n, r.MutableMessage(m, f));  break;
    case FD::TYPE_MESSAGE:  read(n, r.MutableMessage(m, f));  break;
    case FD::TYPE_BYTES:    r.SetString(m, f, str(n));    break;
    case FD::TYPE_ENUM:
        r.SetEnum(m, f, f->enum_type()->FindValueByName(str(n)));
        break;

    default: LOG(ERROR) << "Didn't understand type " << f->type(); break; }
}

void doReadRepeated(const YAML::Node& node, Message* m, const FieldDescriptor* f) {
    const Reflection& r = *m->GetReflection();

    for (uint32 i = 0; i < node.size(); ++i) {
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
        case FD::TYPE_GROUP: read(n, r.AddMessage(m, f));    break;
        case FD::TYPE_MESSAGE: read(n, r.AddMessage(m, f));  break;
        case FD::TYPE_BYTES: r.AddString(m, f, str(n));      break;
        case FD::TYPE_ENUM:
            r.AddEnum(m, f, f->enum_type()->FindValueByName(str(n)));
            break;

        default:
            LOG(ERROR) << "Didn't understand type " << f->type(); break;
        }
    }
}

void read(const YAML::Node& node, Message* to) {
    for (YAML::Iterator i = node.begin(); i != node.end(); ++i) {
        string name = str(i.first());
        if (const FieldDescriptor* f = to->GetDescriptor()->FindFieldByName(name)) {
            if (f->label() == FieldDescriptor::LABEL_REPEATED)
                doReadRepeated(i.second(), to, f);
            else
                read(i.second(), to, f);
        } else {
            LOG(ERROR) << "Couldn't understand field named " << name;
        }
    }
}


// Avoid parsing documents that aren't ours - useful because we parse the
// clip buffer to see if it's our data.
bool isPossiblyData(const string& s) {
    static const char* const opening = "---\ntype: ";
    return !s.find(opening);
}

}  // namespace

bool read(const string& from, Message* to) {
    if (!isPossiblyData(from))
        return false;

    std::istringstream s(from);
    YAML::Parser parser(s);

    YAML::Node node;
    try {
        if (!parser.GetNextDocument(node))
            return false;
    } catch (...) {
        LOG(ERROR) << "Unknown error";
        return false;
    }

    for (YAML::Iterator i = node.begin(); i != node.end(); ++i) {
        string name = str(i.first());
        if (name == "type") {
            string type;
            i.second() >> type;
            if (type != to->GetTypeName()) {
                LOG(ERROR) << "Tried to unserialize " << to->GetTypeName()
                                      << " but found " << type;
                return false;
            }

        } else if (name == "value") {
            read(i.second(), to);

        } else {
            LOG(ERROR) << "Unexpected field " << name;
            return false;
        }
    }

    try {
        if (parser.GetNextDocument(node)) {
            LOG(ERROR) << "More than one document in file";
            return false;
        }
    } catch (...) {
        LOG(ERROR) << "Unknown error 2";
        return false;
    }

    return true;
}

}  // namespace yaml
}  // namespace rec
