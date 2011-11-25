#include "rec/slow/commands/Setters.def.h"

// Created by the command line:
// new --include=command/Command --proto=command::Commands Setters.def

namespace rec {
namespace slow {
namespace commands {

Def<command::Commands> setters(
"command {\n"
  "  type: TOGGLE_GRID_DISPLAY\n"
  "  category: \"Transport\"\n"
  "  is_global_setter: true\n"
  "  address { part: { name: \"show_grid\" } }\n"
  "  setter_type_name: \"rec.slow.GuiSettings\"\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_STRETCH_ENABLE\n"
  "  category: \"Audio\"\n"
  "  is_setter: true\n"
  "  address { part: { name: \"disabled\" } }\n"
  "  setter_type_name: \"rec.audio.stretch.Stretch\"\n"
  "}\n"
  " "
);

}  // namespace commands
}  // namespace slow
}  // namespace rec
