#pragma once

#include "rec/util/Deletable.h"

namespace rec {
namespace util {
namespace thread {
namespace callback {

// A generic callback.
class Callback : public Deletable {
  public:
    Callback() {}
    virtual ~Callback() {}

    virtual bool operator()() = 0;

  private:
    DISALLOW_COPY_ASSIGN_AND_LEAKS(Callback);
};

}  // namespace callback
}  // namespace thread

typedef thread::callback::Callback Callback;

}  // namespace util
}  // namespace rec

