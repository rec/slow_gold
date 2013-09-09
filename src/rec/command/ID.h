#ifndef __REC_COMMAND_COMMANDNAME__
#define __REC_COMMAND_COMMANDNAME__

#include "rec/base/base.h"
#include "rec/command/Command.pb.h"

namespace rec {
namespace command {

// TODO: this is now obsolete.
class ID {
 public:
  enum Index {
    FIRST = 0, PREVIOUS = 1, CURRENT = 2, NEXT = 3, LAST = 4
  };

  ID() {}
  ID(CommandID command) : command_(command) {}
  ID(CommandID command, int index);
  ID(const Command&);

  operator CommandID() const { return command_; }
  CommandID get() const { return command_; }

  const int index() const;
  bool hasIndex() const;

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
  ID& operator++() { ++command_; return *this; }
  ID& operator--() { --command_; return *this; }

  ID operator++(int) {
    ID ret(*this);
    ++command_;
    return ret;
  }

  ID operator--(int) {
    ID ret(*this);
    --command_;
    return ret;
  }

 private:
  CommandID command_;

  JUCE_LEAK_DETECTOR(ID);
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMANDNAME__
