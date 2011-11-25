#include "rec/slow/commands/SlowCommandData.h"
#include "rec/command/CommandData.h"
#include "rec/slow/commands/Commands.def.h"
#include "rec/slow/commands/Descriptions.def.h"
#include "rec/slow/commands/KeyPresses.def.h"
#include "rec/slow/commands/Repeated.def.h"
#include "rec/slow/commands/Setters.def.h"

namespace rec {
namespace slow {

using command::Access;
using command::Commands;
using command::CommandData;

namespace {

class SlowCommandData : public CommandData {
 public:
  SlowCommandData() {}
  const Commands& commands() const { return *commands::commands; }
  const Commands& descriptions(const Access&) const { return *commands::descriptions; }
  const Commands& keyPresses(const Access&) const { return *commands::keyPresses; }
  const Commands& repeated() const { return *commands::repeated; }
  const Commands& setters() const { return *commands::setters; }

 private:
  DISALLOW_COPY_ASSIGN_AND_LEAKS(SlowCommandData);
};

}  // namespace

CommandData* createSlowCommandData() { return new SlowCommandData; }

}  // namespace slow
}  // namespace rec
