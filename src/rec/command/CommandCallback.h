#pragma once

#include "rec/util/thread/Callback.h"

namespace rec {
namespace command {

#define CCALLBACK(ID, NAMESPACE, FUNCTION) \
  void NAMESPACE::FUNCTION(); \
  CommandCallback ID ## FUNCTION(ID, NAMESPACE::FUNCTION)

typedef

class CommandCallback : public Callback {
 public:
  typedef void (*Function)();

  CommandCallback(CommandID id, Function f) : id_(id), function_(f) {}

 private:
  const CommandID id_;
  const Function function_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(CommandCallback);
};

}  // namespace command
}  // namespace rec
