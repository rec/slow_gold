#ifndef __REC_APP_PROGRAM__
#define __REC_APP_PROGRAM__

// A class representing all the things a specific program needs to operate.

#include "rec/base/base.h"
#include "rec/command/Command.pb.h"
#include "rec/app/Menu.pb.h"

namespace rec {
namespace app {

class Program {
 public:
  Program() {}
  virtual ~Program() {}

  virtual command::Commands commands() const = 0;
  virtual command::Commands keypresses() const = 0;
  virtual Menus menus() const = 0;
  virtual MenuCollection menuCollection() const = 0;
  virtual string menuBarName() const = 0;

  virtual bool hasProperty(const string& name) const = 0;
  virtual string makeMenuName(const command::Command&, CommandID) const = 0;
  virtual bool perform(const InvocationInfo&, const command::Command&) = 0;
};

template <typename PARTS>
bool hasProperty(const Program& program, const PARTS& parts) {
  for (auto& part: parts) {
    if (program.hasProperty(part))
      return true;
  }
  return false;
}

}  // namespace app
}  // namespace rec


#endif  // __REC_APP_PROGRAM__
