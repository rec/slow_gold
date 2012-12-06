#include "rec/command/KeyboardBindings.h"

#include "rec/command/map/CommandMap.h"
#include "rec/data/DataOps.h"

namespace rec {
namespace command {

using namespace juce;

void loadKeyboardBindings(ApplicationCommandManager* commandManager) {
  fillKeyPressMappingSet(data::getProto<KeyStrokeCommandMapProto>(global()).map(),
                         commandManager->getKeyMappings()))
}

void saveKeyboardBindings(const CommandMapProto& map) {
  KeyStrokeCommandMapProto mapProto;
  mapProto.mutable_map()->CopyFrom(map);
  data::setProto(mapProto, global());
}

}  // namespace command
}  // namespace rec
