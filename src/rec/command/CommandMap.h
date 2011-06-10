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

  virtual void operator()(const CommandMapProto&);
  const CommandMapProto getProto() const;

  Command getCommand(const Key&) const;
  const vector<Key>& getKeys(Command) const;

  bool invoke(const Key&, ApplicationCommandManager*, bool async = false) const;
  void removeMessage(Command command, int keyIndex);
  void removeKey(const Key& key);
  void add(const Key& key, Command command, int index = -1);

 private:
  typedef std::map<Key, Command> KeyToCommand;
  typedef std::map<Command, vector<Key> > CommandToKeys;

  KeyToCommand toCommand_;
  CommandToKeys toKeys_;

  DISALLOW_COPY_AND_ASSIGN(CommandMap);
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMANDMAP__
