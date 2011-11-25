#include "rec/command/data/SlowCommandData.h"
#include "rec/command/CommandData.h"
#include "rec/command/data/Commands.def.h"
#include "rec/command/data/Descriptions.def.h"
#include "rec/command/data/KeyPresses.def.h"
#include "rec/command/data/Repeated.def.h"
#include "rec/command/data/Setters.def.h"

namespace rec {
namespace command {

namespace {

class SlowCommandData : public CommandData {
 public:
  SlowCommandData() {}
  const Commands& commands() const { return *data::commands; }
  const Commands& descriptions(const Access&) const { return *data::descriptions; }
  const Commands& keyPresses(const Access&) const { return *data::keyPresses; }
  const Commands& repeated() const { return *data::repeated; }
  const Commands& setters() const { return *data::setters; }

 private:
  DISALLOW_COPY_ASSIGN_AND_LEAKS(SlowCommandData);
};

}  // namespace

CommandData* createSlowCommandData() { return new SlowCommandData; }

}  // namespace command
}  // namespace rec
