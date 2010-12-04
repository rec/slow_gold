#ifndef __REC_YAML_INTERNAL__
#define __REC_YAML_INTERNAL__

#include <glog/logging.h>

#include "rec/data/yaml/Yaml.h"
#include "rec/base/BaseNoJuce.h"
#include "rec/data/yaml/include/yaml-cpp/yaml.h"

namespace google {
namespace protobuf {

class EnumValueDescriptor;
class FieldDescriptor;
class Reflection;

}  // namespace google
}  // namespace protobuf


namespace rec {
namespace yaml {

typedef google::protobuf::EnumValueDescriptor EnumValueDescriptor;
typedef google::protobuf::FieldDescriptor FieldDescriptor;
typedef google::protobuf::Reflection Reflection;

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
