#ifndef __REC_COMMAND_COMMANDNAME__
#define __REC_COMMAND_COMMANDNAME__

#include "rec/command/Command.pb.h"

#include "rec/base/base.h"

namespace rec {
namespace command {

class CommandName {
 public:
  typedef Command::Type Type;

  CommandName() {}
  CommandName(CommandID command) : command_(command) {}
  CommandName(CommandID command, int index);

  operator CommandID() const { return command_; }

  const Type type() const;
  const int index() const;
  bool hasIndex() const;
  string name() const;

  bool operator==(const CommandName& x) const { return command_ == x.command_; }
  bool operator!=(const CommandName& x) const { return command_ != x.command_; }
  bool operator>(const CommandName& x) const { return command_ > x.command_; }
  bool operator>=(const CommandName& x) const { return command_ >= x.command_; }
  bool operator<(const CommandName& x) const { return command_ < x.command_; }
  bool operator<=(const CommandName& x) const { return command_ <= x.command_; }
  bool operator!() const { return !command_; }

 private:
  CommandID command_;

  JUCE_LEAK_DETECTOR(CommandName);
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMANDNAME__
