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

  virtual void addCallback(ID, Callback*);

  CommandRecord* find(ID id) { return locate(id, true, false); }
  CommandRecord* create(ID id) { return locate(id, false, true); }
  CommandRecord* findOrCreate(ID id) { return locate(id, false, false); }

  const Commands getCommands() const;

  void fillAllCommands();
  void getAllCommands(juce::Array<CommandID>*) const;

 private:
  CommandRecord* locate(ID id, bool mustExist, bool mustCreate);

  typedef std::map<ID, CommandRecord*> Table;

  CriticalSection lock_;
  Table table_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(CommandRecordTable);
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMANDRECORDTABLE__
