#include "rec/command/data/CommandData.h"
#include "rec/command/data/Commands.def.h"
#include "rec/command/data/Descriptions.def.h"
#include "rec/command/data/KeyPresses.def.h"
#include "rec/command/data/Repeated.def.h"
#include "rec/command/data/Setters.def.h"

namespace rec {
namespace command {

const Commands& commands() { return *data::commands; }
const Commands& descriptions(const Access&) { return *data::descriptions; }
const Commands& keyPresses(const Access&) { return *data::keyPresses; }
const Commands& repeated() { return *data::repeated; }
const Commands& setters() { return *data::setters; }

// Internationalization goes here!

}  // namespace command
}  // namespace rec
