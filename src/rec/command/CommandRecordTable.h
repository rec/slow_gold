#ifndef __REC_COMMAND_COMMANDRECORDTABLE__
#define __REC_COMMAND_COMMANDRECORDTABLE__

#include "rec/command/Command.pb.h"
#include "rec/command/CallbackTable.h"
#include "rec/util/thread/Callback.h"

namespace rec {
namespace command {

struct CommandRecord;

class CommandRecordTable : public CallbackTable {
 public:
  CommandRecordTable() {}
  ~CommandRecordTable();

  virtual void addCallback(CommandID, Callback*);

  CommandRecord* find(CommandID) const;
  CommandRecord* create(CommandID);
  CommandRecord* findOrCreate(CommandID);

  const Commands getCommands() const;

  void getAllCommands(juce::Array<CommandID>*) const;
  void fillAllCommands();
  void fillCommandInfo(CommandID, const String& name, int flags, Enable);

 private:
  typedef std::map<CommandID, CommandRecord*> Table;
  typedef Table::const_iterator const_iterator;

  CriticalSection lock_;
  Table table_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(CommandRecordTable);
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMANDRECORDTABLE__
