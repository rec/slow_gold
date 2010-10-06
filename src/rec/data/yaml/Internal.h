#ifndef __REC_YAML_INTERNAL__
#define __REC_YAML_INTERNAL__

#include <glog/logging.h>

#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>

#include "rec/base/base.h"
#include "rec/data/yaml/Yaml.h"
#include "rec/data/yaml/include/yaml.h"

using google::protobuf::EnumValueDescriptor;
using google::protobuf::FieldDescriptor;
using google::protobuf::Reflection;

namespace rec {
namespace yaml {

typedef FieldDescriptor FD;

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

#endif  // __REC_YAML_INTERNAL__
