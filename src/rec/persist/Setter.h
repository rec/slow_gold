#ifndef __REC_PERSIST_SETTER__
#define __REC_PERSIST_SETTER__

#include "rec/base/basictypes.h"

namespace rec {
namespace persist {




template <typename Proto>
class Setter {
 public:
  struct Arg {
    Arg(const char* s) : string_(s), isString_(true) {}
    Arg(const std::string& s) : string_(s), isString_(true) {}
    Arg(int t) : int_(t), isString_(false) {}

    bool isString_;
    std::string string_;
    int int_;
  };

  void append(const Arg& a1, const Value& v);
};

struct Setter {
  const Message* message_;

  Setter set(const std::string& name) {
    Setter result;
    result
  }
};


as = Setter(Preferences::default_instance()

void Setter(const Message* message) {

}

Setter x();

x.

data->set('foo', 'bar', 0, value);

template <typename iterator>
Address* setter(const google::protobuf::Message& message, Address* address);


struct Setter {
  Address address;
};

function


class Setter {
 public:
  Setter() {}

  void someMethod() {
  }

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(Setter);
};

}  // namespace persist
}  // namespace rec

#endif  // __REC_PERSIST_SETTER__
