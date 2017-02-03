#pragma once

#include "rec/base/base.h"
#include "rec/data/proto/Address.pb.h"

namespace rec {
namespace util {

class MessageMaker {
  public:
    MessageMaker() {}
    virtual ~MessageMaker() {}

    virtual std::unique_ptr<Message> makeMessage(const string& typeName) const = 0;
    virtual data::AddressProto::Scope getScope(const string& typeName) const = 0;
};

}  // namespace util
}  // namespace rec
