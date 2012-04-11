#include "rec/slow/commands/Setters.def.h"

// Created by the command line:
// new --include=command/Command --proto=command::Commands Setters.def

namespace rec {
namespace slow {
namespace commands {

Def<command::Commands> setters(
"command {\n"
  "  type: TOGGLE_COMMAND_BAR_AT_LEFT\n"
  "  is_global_setter: true\n"
  "  address { part: { name: \"command_bar_at_left\" } }\n"
  "  setter_type_name: \"rec.widget.waveform.WaveformProto\"\n"
  "  category: \"Display\"\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_COMMAND_BAR_AT_TOP\n"
  "  is_global_setter: true\n"
  "  address { part: { name: \"command_bar_at_top\" } }\n"
  "  setter_type_name: \"rec.widget.waveform.WaveformProto\"\n"
  "  category: \"Display\"\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_MODES_AT_LEFT\n"
  "  is_global_setter: true\n"
  "  address { part: { name: \"modes_at_left\" } }\n"
  "  setter_type_name: \"rec.widget.waveform.WaveformProto\"\n"
  "  category: \"Display\"\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_MODES_AT_TOP\n"
  "  is_global_setter: true\n"
  "  address { part: { name: \"modes_at_top\" } }\n"
  "  setter_type_name: \"rec.widget.waveform.WaveformProto\"\n"
  "  category: \"Display\"\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_ADVANCED_MENUS\n"
  "  is_global_setter: true\n"
  "  address { part: { name: \"advanced_menus\" } }\n"
  "  setter_type_name: \"rec.slow.GuiSettings\"\n"
  "  category: \"File\"\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_AUTOMATIC_UPDATES\n"
  "  is_global_setter: true\n"
  "  address { part: { name: \"auto_check_for_updates\" } }\n"
  "  setter_type_name: \"rec.slow.GuiSettings\"\n"
  "  category: \"Help\"\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_FOLLOW_CURSOR\n"
  "  is_global_setter: true\n"
  "  address { part: { name: \"follow_cursor\" } }\n"
  "  setter_type_name: \"rec.slow.GuiSettings\"\n"
  "  category: \"Display\"\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_GRID_DISPLAY\n"
  "  is_global_setter: true\n"
  "  address { part: { name: \"show_grid\" } }\n"
  "  setter_type_name: \"rec.widget.waveform.WaveformProto\"\n"
  "  category: \"Display\"\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_FILE_OPEN_TREE_DISPLAY\n"
  "  is_global_setter: true\n"
  "  address { part: { name: \"use_tree_view_in_file_dialogs\" } }\n"
  "  setter_type_name: \"rec.slow.GuiSettings\"\n"
  "  category: \"Display\"\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_PARALLEL_WAVEFORMS\n"
  "  is_global_setter: true\n"
  "  address { part: { name: \"parallel_waveforms\" } }\n"
  "  setter_type_name: \"rec.widget.waveform.WaveformProto\"\n"
  "  category: \"Display\"\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_PREFADER_LEVELS\n"
  "  is_setter: true\n"
  "  address { part: { name: \"prefader_levels\" } }\n"
  "  setter_type_name: \"rec.audio.Gain\"\n"
  "  category: \"Audio\"\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_SHOW_CURSOR_LABELS\n"
  "  is_global_setter: true\n"
  "  address { part: { name: \"show_cursor_labels\" } }\n"
  "  setter_type_name: \"rec.widget.waveform.WaveformProto\"\n"
  "  category: \"Display\"\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_SHOW_LABELS_AT_TOP\n"
  "  is_global_setter: true\n"
  "  address { part: { name: \"show_labels_at_top\" } }\n"
  "  setter_type_name: \"rec.widget.waveform.WaveformProto\"\n"
  "  category: \"Display\"\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_SHOW_TIMES_AT_TOP\n"
  "  is_global_setter: true\n"
  "  address { part: { name: \"show_times_at_top\" } }\n"
  "  setter_type_name: \"rec.widget.waveform.WaveformProto\"\n"
  "  category: \"Display\"\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_SHOW_SELECTION_BUTTONS\n"
  "  is_global_setter: true\n"
  "  address { part: { name: \"show_selection_buttons\" } }\n"
  "  setter_type_name: \"rec.widget.waveform.WaveformProto\"\n"
  "  category: \"Display\"\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_STRETCH_ENABLE\n"
  "  is_setter: true\n"
  "  address { part: { name: \"enabled\" } }\n"
  "  setter_type_name: \"rec.audio.stretch.Stretch\"\n"
  "  category: \"Audio\"\n"
  "}\n"
  " "
);

}  // namespace commands
}  // namespace slow
}  // namespace rec
