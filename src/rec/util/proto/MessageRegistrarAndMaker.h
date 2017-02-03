#pragma once

#include "rec/data/proto/Address.pb.h"
#include "rec/util/proto/MessageMaker.h"
#include "rec/util/proto/MessageRegistrar.h"

namespace rec {
namespace util {

class MessageRegistrarAndMaker : public MessageRegistrar, public MessageMaker {
 public:
  MessageRegistrarAndMaker();
  virtual ~MessageRegistrarAndMaker();

  std::unique_ptr<Message> makeMessage(const string& typeName) const override;
  void registerInstance(
      const Message& m, bool copy, data::AddressProto::Scope) override;
  data::AddressProto::Scope getScope(const string& typeName) const override;

 private:
  struct Impl;
  std::unique_ptr<Impl> impl_;
  DISALLOW_COPY_ASSIGN_AND_LEAKS(MessageRegistrarAndMaker);
};

}  // namespace util
}  // namespace rec
