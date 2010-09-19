#include "rec/proto/Address.h"

namespace rec {
namespace proto {

Address::Address(Tag t1) {
  tags_.push_back(t1);
}

Address::Address(Tag t1, Tag t2) {
  tags_.push_back(t1);
  tags_.push_back(t2);
}

Address::Address(Tag t1, Tag t2, Tag t3) {
  tags_.push_back(t1);
  tags_.push_back(t2);
  tags_.push_back(t3);
}

Address::Address(Tag t1, Tag t2, Tag t3, Tag t4) {
  tags_.push_back(t1);
  tags_.push_back(t2);
  tags_.push_back(t3);
  tags_.push_back(t4);
}

Operation* Address::addToOperation(Operation* op) const {
  for (TagList::const_iterator i = tags_.begin(); i != tags_.end(); ++i)
    op->add_address(*i);
  return op;
}


}  // namespace proto
}  // namespace rec
