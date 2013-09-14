#include "rec/command/KeyboardBindings.h"

#include "rec/command/map/CommandMap.h"
#include "rec/command/map/Editor.h"
#include "rec/slow/commands/Command.pb.h"
#include "rec/slow/commands/SlowCommandData.h"
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
      mappings->addKeyPress(m.id(), keyPressFromString(m.key(j)));
  }
}

}  // namespace

CommandMapProto getKeyboardBindings() {
  data::Data* d = data::getData<KeyStrokeCommandMapProto>(data::global());
  if (d->fileReadSuccess())
    return getProto<KeyStrokeCommandMapProto>(d).map();

  static const KeyStrokeCommandMapProto mp = slow::makeKeyBindings();
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
