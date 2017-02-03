#pragma once

#include "rec/base/base.h"
#include "rec/util/Binary.h"

namespace rec {
namespace util {

bool fillFromDefault(const string&, Message*);

template <typename Proto>
class Def {
  public:
    explicit Def(const string& dflt) { fillFromDefault(dflt, &proto_); }
    const Proto& get() const { return proto_; }
    const Proto& operator*() const { return get(); }

  private:
    Proto proto_;
};

template <typename Proto>
class DefBinary : public Def<Proto> {
    explicit DefBinary(const char* resource, int length)
            : Def<Proto>(string(resource, length)) {}
};

}  // namespace util
}  // namespace rec
