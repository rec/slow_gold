#ifndef __REC_COMMAND_COMMANDNAME__
#define __REC_COMMAND_COMMANDNAME__

#include "rec/command/Command.pb.h"

#include "rec/base/base.h"

namespace rec {
namespace command {

class ID {
 public:
  typedef Command::Type Type;

  enum Index {
    FIRST = -5, PREVIOUS = -4, CURRENT = -3, NEXT = -2, LAST = -1
  };

  ID() {}
  ID(CommandID command) : command_(command) {}
  ID(CommandID command, int index);

  operator CommandID() const { return command_; }

  const Type type() const;
  const int index() const;
  bool hasIndex() const;
  string name() const;

  bool operator==(const ID& x) const { return command_ == x.command_; }
  bool operator!=(const ID& x) const { return command_ != x.command_; }
  bool operator>(const ID& x) const { return command_ > x.command_; }
  bool operator>=(const ID& x) const { return command_ >= x.command_; }
  bool operator<(const ID& x) const { return command_ < x.command_; }
  bool operator<=(const ID& x) const { return command_ <= x.command_; }

  bool operator==(const int32& x) const { return command_ == x; }
  bool operator!=(const int32& x) const { return command_ != x; }
  bool operator>(const int32& x) const { return command_ > x; }
  bool operator>=(const int32& x) const { return command_ >= x; }
  bool operator<(const int32& x) const { return command_ < x; }
  bool operator<=(const int32& x) const { return command_ <= x; }

  bool operator!() const { return !command_; }

 private:
  CommandID command_;

  JUCE_LEAK_DETECTOR(ID);
};

inline std::ostream& operator<<(std::ostream& os, const ID& id)
{
  os << id.name();
  return os;
}

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMANDNAME__
