#pragma once

#include <map>

#include "rec/command/map/CommandMap.pb.h"
#include "rec/util/Listener.h"

namespace rec {
namespace command {

class CommandMap : public ChangeBroadcaster {
 public:
  typedef vector<string> KeyVector;

  CommandMap() {}
  virtual ~CommandMap() {}
  void addCommands(const CommandMapProto&);

  const CommandMapProto getProto() const;

  CommandID getCommand(const string&) const;
  const KeyVector& getKeys(CommandID) const;

  bool invokeAsync(const string&, ApplicationCommandManager*) const;

  void removeCommand(CommandID command, uint keyIndex);
  void removeKey(const string& key);

  bool addAtIndex(const string& key, CommandID command, int index);

 private:
  bool add(const string& key, CommandID command);
  bool addKey(const string& key, CommandID command);
  void dump() const;

  typedef std::map<string, CommandID> KeyToCommand;
  typedef std::map<CommandID, KeyVector> CommandToKeys;

  KeyToCommand toCommand_;
  CommandToKeys toKeys_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(CommandMap);
};

}  // namespace command
}  // namespace rec

