#ifndef __REC_PROTO_APPLIER__
#define __REC_PROTO_APPLIER__

#include <iostream.h>

#include "rec/base/base.h"
#include "rec/base/basictypes.h"
#include "rec/proto/Proto.pb.h"

namespace rec {
namespace proto {

class Applier {
 public:
  typedef google::protobuf::FieldDescriptor FieldDescriptor;
  typedef google::protobuf::Message Message;

  Applier(const Operation& op, Message* msg, const FieldDescriptor* f);
  Applier(int index, const Operation& op, Message* m, const FieldDescriptor* f);

  static Applier* create(const Operation& op, Message* msg);

  bool apply();

 private:
  bool clear();
  bool set();
  bool add();
  bool removeLast();
  bool swap();
  bool hasValueField();

  friend std::ostream& operator<<(std::ostream& os, const Applier& applier);

  const Operation& operation_;
  Message* const message_;
  const FieldDescriptor* const field_;
  const int index_;
  const bool isIndexed_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Applier);
};

}  // namespace proto
}  // namespace rec

#endif  // __REC_PROTO_APPLIER__
