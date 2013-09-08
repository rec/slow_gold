#ifndef __REC_COMMAND_COMMANDRECORDTABLE__
#define __REC_COMMAND_COMMANDRECORDTABLE__

#include <map>

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

  void addCallback(ID, unique_ptr<Callback>) override;

  CommandRecord* find(ID id) { return locate(id, true, false); }
  CommandRecord* create(ID id) { return locate(id, false, true); }
  CommandRecord* findOrCreate(ID id) { return locate(id, false, false); }

  const Commands getCommands() const;

  void fillAllCommands();
  void getAllCommands(juce::Array<CommandID>*) const;

  // Used for new-style callbacks.
  typedef std::map<ID, CommandRecord*> Table;
  Table* table() { return &table_; }

 private:
  CommandRecord* locate(ID id, bool mustExist, bool mustCreate);

  CriticalSection lock_;
  Table table_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(CommandRecordTable);
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMANDRECORDTABLE__
