#pragma once

#include "rec/command/map/CommandMap.pb.h"
#include "rec/program/Types.h"
#include "rec/gui/proto/Constants.h"

namespace rec {
namespace program {

class Program;

CommandMap makeCommandMap(const Program&);
MenuMap makeMenuMap(const Program&);
MenuBarMap makeMenuBarMap(const Program&);
ThreadMap makeThreadMap(const Program&);
LayoutMap makeLayoutMap(const Program&);
command::CommandMapProto makeKeyMap(const Program&);
void mergeKeysIntoCommands(const command::CommandMapProto&, CommandMap*);
gui::Constants makeConstants();

}  // namespace program
}  // namespace rec
