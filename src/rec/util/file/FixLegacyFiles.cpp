#include "rec/util/file/FixLegacyFiles.h"

#include "rec/command/CommandMap.pb.h"
#include "rec/command/CommandIDEncoder.h"
#include "rec/data/DataOps.h"
#include "rec/util/file/MoveFile.h"
#include "rec/util/file/TypeMap.h"

namespace rec {
namespace util {
namespace file {

namespace {

using namespace rec::command;

CommandMapEntry* newEntry(Command::Type type, const String& key,
                          KeyStrokeCommandMapProto* keyMap) {
  CommandMapEntry* entry = keyMap->add_entry();
  entry->set_command(type);
  entry->set_key(str(key));
  return entry;
}

void portKeyboardFile() {
  File f = keyboardFile();
  if (f.exists()) {
    Commands commands;
    if (copy::copy(f, &commands)) {
      KeyStrokeCommandMapProto keyMap;
      for (int i = 0; i < commands.command_size(); ++i) {
        const Command& command = commands.command(i);
        Command::Type type = command.type();
        if (command.has_start_index()) {
          int32 index = command.start_index();
          for (int j = 0; j < command.keypress_size(); ++j, ++)
            newEntry(type, command.keypress(j), &keyMap)->set_index(index);

        } else {
          for (int j = 0; j < command.keypress_size(); ++j, ++)
            newEntry(type, command.keypress(j), &keyMap);
        }
      }
      data::setProto(keyMap, data::global());
      f.deleteFile();
   }
  }
}

}

void moveOldAbsoluteDirectoriesToTypeRelative() {
  const TypeMap& map = getTypeMap();
  for (TypeMap::const_iterator i = map.begin(); i != map.end(); ++i)
    moveTypeDirectory(i->first, i->second.first);
  moveGlobalFiles();
  moveKeyboardFile();
}

void fixLegacyFiles() {
  moveOldAbsoluteDirectoriesToTypeRelative();
  portKeyboardFile();
}

}  // namespace file
}  // namespace util
}  // namespace rec
