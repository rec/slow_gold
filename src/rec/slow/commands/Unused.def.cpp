#include "rec/slow/commands/Unused.def.h"

// Created by the command line:
// new --include=command/Command --proto=command::Commands src/rec/slow/commands/Unused.def

namespace rec {
namespace slow {
namespace commands {

Def<command::Commands> unused(
"command {\n"
  "  type: NUDGE_BEGIN_LEFT\n"
  "  desc {\n"
  "    menu: \"Nudge segment start left.\"\n"
  "    full: \"Nudge segment start left.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: NUDGE_BEGIN_RIGHT\n"
  "  desc {\n"
  "    menu: \"Nudge segment start right.\"\n"
  "    full: \"Nudge segment start right.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: NUDGE_END_LEFT\n"
  "  desc {\n"
  "    menu: \"Nudge segment end left.\"\n"
  "    full: \"Nudge segment end left.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: NUDGE_END_RIGHT\n"
  "  desc {\n"
  "    menu: \"Nudge segment end right.\"\n"
  "    full: \"Nudge segment end right.\"\n"
  "  }\n"
  "}\n"
  "\n"
  "command { type: NUDGE_BEGIN_LEFT category: \"Loops\"}\n"
  "command { type: NUDGE_BEGIN_RIGHT category: \"Loops\"}\n"
  "command { type: NUDGE_END_LEFT category: \"Loops\"}\n"
  "command { type: NUDGE_END_RIGHT category: \"Loops\"}\n"
  "\n"
  "  add(c, Command::NUDGE_BEGIN_LEFT, nudgeBeginLeft, i);\n"
  "  add(c, Command::NUDGE_BEGIN_RIGHT, nudgeBeginRight, i);\n"
  "  add(c, Command::NUDGE_END_LEFT, nudgeEndLeft, i);\n"
  "  add(c, Command::NUDGE_END_RIGHT, nudgeEndRight, i);\n"
  "\n"
  "command { type: TREE_CLOSE category: \"\"}\n"
  "command { type: TREE_DOWN category: \"\"}\n"
  "command { type: TREE_LEFT category: \"\"}\n"
  "command { type: TREE_OPEN category: \"\"}\n"
  "command { type: TREE_RIGHT category: \"\"}\n"
  "command { type: TREE_UP category: \"\"}\n"
  "\n"
  "  add(c, Command::TREE_CLOSE, treeClose, i);\n"
  "  add(c, Command::TREE_DOWN, treeDown, i);\n"
  "  add(c, Command::TREE_LEFT, treeLeft, i);\n"
  "  add(c, Command::TREE_OPEN, treeOpen, i);\n"
  "  add(c, Command::TREE_RIGHT, treeRight, i);\n"
  "  add(c, Command::TREE_UP, treeUp, i);\n"
  "\n"
  "command { type: ZOOM_IN category: \"Audio\"}\n"
  " "
);

}  // namespace commands
}  // namespace slow
}  // namespace rec
