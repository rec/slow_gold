#ifndef __REC_COMMAND_COMMAND__
#define __REC_COMMAND_COMMAND__

#include "rec/util/thread/Callback.h"
#include "rec/command/Command.pb.h"
#include "rec/command/CommandItemSetter.h"
#include "rec/util/Listener.h"

namespace rec {
namespace command {

struct CommandRecord {
  explicit CommandRecord(CommandID id) : info_(id) {}

  ptr<Command> command_;
  ptr<Callback> callback_;
  ptr<CommandItemSetter> setter_;
  ApplicationCommandInfo info_;

 private:
  DISALLOW_COPY_ASSIGN_AND_LEAKS(CommandRecord);
};

class CommandRecordTable {
 public:
  CommandRecordTable() {}
  ~CommandRecordTable();

  typedef std::map<CommandID, CommandRecord*> Table;

  typedef Table::iterator iterator;
  typedef Table::const_iterator const_iterator;

  CommandRecord* find(CommandID id, bool create = true);
  void erase(CommandID id) { table_.erase(id); }
  const Commands getCommands() const;

  iterator begin() { return table_.begin(); }
  iterator end() { return table_.end(); }
  const_iterator begin() const { return table_.begin(); }
  const_iterator end() const { return table_.end(); }
  void writeTable() const;

 private:
  Table table_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(CommandRecordTable);
};

string commandName(CommandID);

extern const CommandID JUMP_TO_FIRST;

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMAND__
