#ifndef __REC_COMMAND_COMMANDRECORDTABLE__
#define __REC_COMMAND_COMMANDRECORDTABLE__

#include "rec/base/base.h"

#include "rec/command/Command.pb.h"

namespace rec {
namespace command {

class CommandRecord;

class CommandRecordTable {
 public:
  CommandRecordTable() {}
  ~CommandRecordTable();

  typedef std::map<CommandID, CommandRecord*> Table;

  typedef Table::iterator iterator;
  typedef Table::const_iterator const_iterator;

  CommandRecord* find(CommandID id, bool create = true);

  void erase(CommandID id) {
    Lock l(lock_);
    table_.erase(id);
  }

  const Commands getCommands() const;

  iterator begin() { return table_.begin(); }
  iterator end() { return table_.end(); }
  const_iterator begin() const { return table_.begin(); }
  const_iterator end() const { return table_.end(); }

 private:
  CriticalSection lock_;
  Table table_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(CommandRecordTable);
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMANDRECORDTABLE__
