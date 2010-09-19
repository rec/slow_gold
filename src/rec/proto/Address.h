#ifndef __REC_PROTO_ADDRESS__
#define __REC_PROTO_ADDRESS__

#include <vector>
#include "rec/base/basictypes.h"
#include "rec/proto/Types.h"

namespace rec {
namespace proto {

class Address {
 public:
  Address() {}
  Address(Tag t1);
  Address(Tag t1, Tag t2);
  Address(Tag t1, Tag t2, Tag t3);
  Address(Tag t1, Tag t2, Tag t3, Tag t4);
  Operation* addToOperation(Operation* op) const;

 private:
  typedef std::vector<Tag> TagList;
  TagList tags_;
};


}  // namespace proto
}  // namespace rec

#endif  // __REC_PROTO_ADDRESS__
