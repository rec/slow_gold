#ifndef __REC_PROTO_APPLIER__
#define __REC_PROTO_APPLIER__

#include "rec/base/basictypes.h"
#include "rec/proto/Proto.h"

namespace rec {
namespace proto {

class Applier {
 public:
  Applier(const Operation& operation, Message* msg, FieldDescriptor* field);

  Applier(int index, const Operation& operation,
          Message* msg, FieldDescriptor* field);

  static Applier* newApplier(const Address& address, const Operation& op,
                             Message* msg);

  bool apply();

 private:
  bool clear();
  bool set();
  bool add();
  bool removeLast();
  bool swap();

 private:
  bool hasValueField();

  const Operation& operation_;
  Message* const message_;
  FieldDescriptor* const field_;
  const bool isIndexed_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Applier);
};

}  // namespace proto
}  // namespace rec

#endif  // __REC_PROTO_APPLIER__
