#include "rec/command/data/CommandData.h"
#include "rec/command/data/Commands.def.h"
#include "rec/command/data/Descriptions.def.h"
#include "rec/command/data/KeyPresses.def.h"

namespace rec {
namespace command {

const Commands& commands() { return *data::commands; }
const Commands& descriptions(const Access&) { return *data::descriptions; }
const Commands& keyPresses(const Access&) { return *data::keyPresses; }

// Internationalization goes here!

}  // namespace command
}  // namespace rec
