#ifndef __REC_COMMAND_COMMANDMAP__
#define __REC_COMMAND_COMMANDMAP__

#include <map>

#include "rec/command/CommandRecord.h"
#include "rec/command/map/CommandMap.pb.h"
#include "rec/util/Listener.h"

namespace rec {
namespace command {

class CommandMap : public ChangeBroadcaster {
 public:
  typedef command::Command::Type CommandType;
  typedef vector<string> KeyVector;

  CommandMap() {}
  virtual ~CommandMap() {}
  void addCommands(const CommandMapProto&);

  const CommandMapProto getProto() const;

  CommandType getCommand(const string&) const;
  const KeyVector& getKeys(CommandType) const;

  bool invokeAsync(const string&, ApplicationCommandManager*) const;

  void removeCommand(CommandType command, uint keyIndex);
  void removeKey(const string& key);

  bool addAtIndex(const string& key, CommandType command, int index);

 private:
  bool add(const string& key, CommandType command);
  bool addKey(const string& key, CommandType command);

  typedef std::map<string, CommandType> KeyToCommand;
  typedef std::map<CommandType, KeyVector> CommandToKeys;

  KeyToCommand toCommand_;
  CommandToKeys toKeys_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(CommandMap);
};

void fillKeyPressMappingSet(const CommandMapProto&, juce::KeyPressMappingSet*);

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMANDMAP__
