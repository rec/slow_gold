#include "rec/command/KeyboardBindings.h"

#include "rec/command/map/CommandMap.h"
#include "rec/command/map/Editor.h"
#include "rec/slow/commands/SlowCommand.pb.h"
#include "rec/data/DataOps.h"
#include "rec/util/Binary.h"

namespace rec {
namespace command {

using namespace juce;
using namespace rec::data;

namespace {

void fillKeyPressMappingSet(const CommandMapProto& commandMap,
                            KeyPressMappingSet* mappings) {
  mappings->clearAllKeyPresses();
  for (int i = 0; i < commandMap.entry_size(); ++i) {
    const CommandMapEntry& m = commandMap.entry(i);
    for (int j = 0; j < m.key_size(); ++j)
      mappings->addKeyPress(m.command(), keyPressFromString(m.key(j)));
  }
}

KeyStrokeCommandMapProto makeKeyBindings() {
  slow::SlowCommandMapProto slowMaps =
    BINARY_PROTO(SlowKeyStrokeMap_def, slow::SlowCommandMapProto);

  KeyStrokeCommandMapProto bindings;
  auto map = bindings.mutable_map();
  for (auto& slowEntry: slowMaps.slow_entry()) {
    auto entry = map->add_entry();
    *entry = slowEntry.entry();
    entry->set_command(slowEntry.type());
  }
  return bindings;
}



}  // namespace

CommandMapProto getKeyboardBindings() {
  data::Data* d = data::getData<KeyStrokeCommandMapProto>(data::global());
  if (d->fileReadSuccess())
    return getProto<KeyStrokeCommandMapProto>(d).map();

  static const KeyStrokeCommandMapProto mp = makeKeyBindings();
    //   BINARY_PROTO(KeyStrokeMap_def,  KeyStrokeCommandMapProto);
  return mp.map();
}

void loadKeyboardBindings(ApplicationCommandManager* commandManager) {
  fillKeyPressMappingSet(getKeyboardBindings(),
                         commandManager->getKeyMappings());
}

void saveKeyboardBindings(const CommandMapProto& map) {
  KeyStrokeCommandMapProto mapProto;
  mapProto.mutable_map()->CopyFrom(map);
  data::setProto(mapProto, global());
}

}  // namespace command
}  // namespace rec
