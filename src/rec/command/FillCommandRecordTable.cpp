#include "rec/command/FillCommandRecordTable.h"
#include "rec/command/CommandDatabase.h"

namespace rec {
namespace command {

void fillCommandRecordTable(CommandRecordTable* table, const CommandData& data) {
  CommandDatabase(table, data).fill();
}

}  // namespace command
}  // namespace rec
