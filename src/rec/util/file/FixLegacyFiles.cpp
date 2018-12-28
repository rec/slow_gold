#include "rec/util/file/FixLegacyFiles.h"

#include "rec/command/Command.pb.h"
#include "rec/command/map/CommandMap.pb.h"
#include "rec/data/DataOps.h"
#include "rec/util/Copy.h"
#include "rec/util/file/MoveFile.h"
#include "rec/util/file/TypeMap.h"

namespace rec {
namespace util {
namespace file {

namespace {

using namespace rec::command;
using namespace rec::data;

CommandMapEntry* newEntry(CommandID id, KeyStrokeCommandMapProto* map) {
    auto entry = map->mutable_map()->add_entry();
    entry->set_id(id);
    return entry;
}

void portKeyboardFile() {
    auto f = keyboardFile().getChildFile(str(getTypeName<Commands>()));
    if (not f.exists())
        return;
    Commands commands;
    auto copied = copy::copy(f, &commands);
    DCHECK(copied) << "Couldn't copy file " << str(f);
    if (not copied)
        return;

    KeyStrokeCommandMapProto keyMap;
    for (int i = 0; i < commands.command_size(); ++i) {
        auto& command = commands.command(i);
        auto type = command.id();
        // TODO: https://github.com/rec/rec/issues/621
#ifdef UNUSED_CODE
        if (false) { // command.has_start_index()) {
            int32 index = 0; // command.start_index();
            for (int j = 0; j < command.keypress_size(); ++j, ++index) {
                auto entry = newEntry(type, &keyMap);
                entry->set_index(index);
                entry->add_key(command.keypress(j));
            }
        } else {
        }
#endif
        auto entry = newEntry(type, &keyMap);
        for (int j = 0; j < command.keypress_size(); ++j)
            entry->add_key(command.keypress(j));
    }

    data::setProto(keyMap, data::global());
    auto parent = f.getParentDirectory();
    auto deleted = f.deleteFile();
    DCHECK(deleted) << str(f);
    deleted = parent.deleteFile();
    DCHECK(deleted) << str(parent);
}

void moveOldAbsoluteDirectoriesToTypeRelative() {
    for (auto& i: getTypeMap())
        moveTypeDirectory(i.first, i.second.first);
    moveGlobalFiles();
    moveKeyboardFile();
}

template <typename OLD, typename NEW, typename CONVERTER>
void moveGlobalData(CONVERTER converter) {
    auto newData = data::getData<NEW>(data::global());
    if (newData->fileReadSuccess())
        return;

    auto oldData = data::getData<OLD>(data::global());
    if (not oldData->fileReadSuccess())
        return;

    data::Opener<NEW> opener(newData, CANT_UNDO);
    converter(data::getProto<OLD>(oldData), opener.get());
}

}  // namespace

void fixLegacyFiles() {
    moveOldAbsoluteDirectoriesToTypeRelative();
    portKeyboardFile();
}

}  // namespace file
}  // namespace util
}  // namespace rec
