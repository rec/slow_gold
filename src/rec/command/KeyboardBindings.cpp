#include "rec/command/KeyboardBindings.h"

#include "rec/command/map/CommandMap.h"
#include "rec/command/map/Editor.h"
#include "rec/data/DataOps.h"
#include "rec/slow/commands/Command.pb.h"
#include "rec/program/JuceModel.h"
#include "rec/util/BinaryMacros.h"

namespace rec {
namespace command {

using namespace juce;
using namespace rec::data;

namespace {

void fillKeyPressMappingSet(const CommandMapProto& commandMap,
                            KeyPressMappingSet* mappings) {
  mappings->clearAllKeyPresses();
  DLOG(INFO) << "!!!!!! " << commandMap.entry_size();
  for (int i = 0; i < commandMap.entry_size(); ++i) {
    const CommandMapEntry& m = commandMap.entry(i);
    DLOG(INFO) << m.key_size() << ": " << m.id();
    for (int j = 0; j < m.key_size(); ++j)
      mappings->addKeyPress(m.id(), keyPressFromString(m.key(j)));
  }
}

}  // namespace

CommandMapProto getKeyboardBindings() {
  data::Data* d = data::getData<KeyStrokeCommandMapProto>(data::global());
  if (d->fileReadSuccess())
    return getProto<KeyStrokeCommandMapProto>(d).map();
  else
    return BINARY_PROTO(KeyStrokeMap, CommandMapProto);
}

void loadKeyboardBindings(ApplicationCommandManager* commandManager) {
  // getKeyboardBindings(),

  fillKeyPressMappingSet(program::juceModel()->keyMap(),
                         commandManager->getKeyMappings());
}

void saveKeyboardBindings(const CommandMapProto& map) {
  KeyStrokeCommandMapProto mapProto;
  mapProto.mutable_map()->CopyFrom(map);
  data::setProto(mapProto, global());
}

}  // namespace command
}  // namespace rec
