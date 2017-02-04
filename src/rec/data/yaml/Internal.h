#pragma once

#include "rec/data/yaml/Yaml.h"
#include "yaml-cpp/yaml.h"
#include "rec/base/base.h"

namespace google {
namespace protobuf {

class EnumValueDescriptor;
class FieldDescriptor;
class Reflection;

}  // namespace google
}  // namespace protobuf


namespace rec {
namespace yaml {

using EnumValueDescriptor = google::protobuf::EnumValueDescriptor;
using FieldDescriptor = google::protobuf::FieldDescriptor;
using Reflection = google::protobuf::Reflection;

using FD = FieldDescriptor;

struct MessageField {
    MessageField(const Message* m, const FieldDescriptor* f)
            : message_(m), field_(f) {
    }
    const Message* message_;
    const FieldDescriptor* field_;
};

struct MessageFieldIndex : public MessageField {
    MessageFieldIndex(const Message* m, const FieldDescriptor* f)
            : MessageField(m, f) {
    }

    MessageFieldIndex(const MessageField& mf, int i)
            : MessageField(mf), index_(i) {
    }
    int index_;
};


}  // namespace yaml
}  // namespace rec
