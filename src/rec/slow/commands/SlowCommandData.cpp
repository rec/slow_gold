#include "rec/slow/commands/SlowCommandData.h"
#include "rec/slow/commands/Command.pb.h"

namespace rec {
namespace slow {

command::KeyStrokeCommandMapProto makeKeyBindings() {
  slow::CommandMapProto slowMaps =
    BINARY_PROTO(KeyStrokeMap, slow::CommandMapProto);

  command::KeyStrokeCommandMapProto bindings;
  auto map = bindings.mutable_map();
  for (auto& slowEntry: slowMaps.entry()) {
    auto entry = map->add_entry();
    *entry = slowEntry.entry();
    entry->set_id(slowEntry.id());
  }
  return bindings;
}

}  // namespace slow
}  // namespace rec
