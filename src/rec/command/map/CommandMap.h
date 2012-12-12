#ifndef __REC_COMMAND_COMMANDMAP__
#define __REC_COMMAND_COMMANDMAP__

#include <map>

#include "rec/command/CommandRecord.h"
#include "rec/command/map/CommandMap.pb.h"
#include "rec/command/ID.h"
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

  ID getCommand(const string&) const;
  const KeyVector& getKeys(ID) const;

  bool invokeAsync(const string&, ApplicationCommandManager*) const;

  void removeCommand(ID command, uint keyIndex);
  void removeKey(const string& key);

  bool addAtIndex(const string& key, ID command, int index);

 private:
  bool add(const string& key, ID command);
  bool addKey(const string& key, ID command);
  void dump() const;

  typedef std::map<string, ID> KeyToCommand;
  typedef std::map<ID, KeyVector> CommandToKeys;

  KeyToCommand toCommand_;
  CommandToKeys toKeys_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(CommandMap);
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMANDMAP__
