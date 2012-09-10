#ifndef __REC_COMMAND_COMMANDRECORDTABLE__
#define __REC_COMMAND_COMMANDRECORDTABLE__

#include "rec/base/base.h"

#include "rec/command/Command.pb.h"
#include "rec/util/thread/Callback.h"

namespace rec {
namespace command {

class CommandRecord;

class CommandRecordTable {
 public:
  CommandRecordTable() {}
  ~CommandRecordTable();

  CommandRecord* find(CommandID id, bool create = true);

  void erase(CommandID);
  const Commands getCommands() const;
  void getAllCommands(juce::Array<CommandID>*);
  void fillCommandInfo();

 private:
  typedef std::map<CommandID, Callback*> CallbackTable;

  typedef std::map<CommandID, CommandRecord*> Table;
  typedef Table::const_iterator const_iterator;

  CriticalSection lock_;
  Table table_;
  CallbackTable callbacks_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(CommandRecordTable);
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMANDRECORDTABLE__
