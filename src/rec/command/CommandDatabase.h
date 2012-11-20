#ifndef __REC_COMMAND_COMMANDDATABASE__
#define __REC_COMMAND_COMMANDDATABASE__

#include "rec/base/base.h"

namespace rec {
namespace command {

class Command;
class CommandData;
class CommandRecordTable;

class CommandDatabase {
 public:
  CommandDatabase(CommandRecordTable*, const CommandData&);
  void fill();

 private:
  void fillSingleCommand(const Command&);
  void fillRepeatingCommand(const Command&);

 private:
  CommandRecordTable* table_;
  const CommandData& data_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(CommandDatabase);
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMANDDATABASE__
