#ifndef __REC_COMMAND_COMMANDMAP__
#define __REC_COMMAND_COMMANDMAP__

#include <map>

#include "rec/command/CommandMap.pb.h"
#include "rec/util/listener/Listener.h"

namespace rec {
namespace command {

class CommandMap : public Listener<const CommandMapProto&> {
 public:
  typedef command::Command::Type Command;
  typedef string Key;

  CommandMap() {}
  virtual ~CommandMap() {}

  void operator()(const CommandMapProto&);
  const CommandMapProto getProto() const;

  Command getCommand(const Key&) const;
  const Key getKey(Command) const;

  bool invoke(const Key&, ApplicationCommandManager*, bool async = false) const;

 private:
  typedef std::map<Key, Command> KeyToCommand;
  typedef std::map<Command, Key> CommandToKey;

  KeyToCommand toCommand_;
  CommandToKey toKey_;

  DISALLOW_COPY_AND_ASSIGN(CommandMap);
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMANDMAP__
