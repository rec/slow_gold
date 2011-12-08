#include "rec/slow/commands/Setters.def.h"

// Created by the command line:
// new --include=command/Command --proto=command::Commands Setters.def

namespace rec {
namespace slow {
namespace commands {

Def<command::Commands> setters(
"command {\n"
  "  type: FOLLOW_CURSOR\n"
  "  is_global_setter: true\n"
  "  address { part: { name: \"follow_cursor\" } }\n"
  "  setter_type_name: \"rec.slow.GuiSettings\"\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_GRID_DISPLAY\n"
  "  is_global_setter: true\n"
  "  address { part: { name: \"show_grid\" } }\n"
  "  setter_type_name: \"rec.widget.waveform.WaveformProto\"\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_PARALLEL_WAVEFORMS\n"
  "  is_global_setter: true\n"
  "  address { part: { name: \"parallel_waveforms\" } }\n"
  "  setter_type_name: \"rec.widget.waveform.WaveformProto\"\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_PREFADER_LEVELS\n"
  "  is_setter: true\n"
  "  address { part: { name: \"prefader_levels\" } }\n"
  "  setter_type_name: \"rec.audio.Gain\"\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_STRETCH_ENABLE\n"
  "  is_setter: true\n"
  "  address { part: { name: \"enabled\" } }\n"
  "  setter_type_name: \"rec.audio.stretch.Stretch\"\n"
  "}\n"
  " "
);

}  // namespace commands
}  // namespace slow
}  // namespace rec
