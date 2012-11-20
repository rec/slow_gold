#ifndef __REC_COMMAND_COMMANDMAP__
#define __REC_COMMAND_COMMANDMAP__

#include <map>

#include "rec/command/CommandRecord.h"
#include "rec/command/map/CommandMap.pb.h"
#include "rec/util/Listener.h"

namespace rec {
namespace command {

class CommandMap {
 public:
  typedef command::Command::Type CommandType;
  typedef string Key;
  typedef vector<Key> KeyVector;

  CommandMap() {}
  virtual ~CommandMap() {}

  void addCommands(const CommandMapProto&);

  const CommandMapProto getProto() const;

  CommandType getCommand(const Key&) const;
  const KeyVector& getKeys(CommandType) const;

  bool invokeAsync(const Key&, ApplicationCommandManager*) const;

  void removeCommand(CommandType command, uint keyIndex);
  void removeKey(const Key& key);

  bool addAtIndex(const Key& key, CommandType command, uint index);

 private:
  bool add(const Key& key, CommandType command);
  bool addKey(const Key& key, CommandType command);

  typedef std::map<Key, CommandType> KeyToCommand;
  typedef std::map<CommandType, KeyVector> CommandToKeys;

  KeyToCommand toCommand_;
  CommandToKeys toKeys_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(CommandMap);
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMANDMAP__
