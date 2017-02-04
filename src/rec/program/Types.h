#pragma once

#include <unordered_map>

#include "rec/gui/proto/Layout.pb.h"
#include "rec/gui/proto/Component.pb.h"
#include "rec/program/Menu.pb.h"
#include "rec/util/thread/Callback.h"

namespace rec {
namespace program {

using CommandMap = std::unordered_map<CommandID, command::Command>;
using MenuMap = std::unordered_map<string, Menu>;
using MenuBarMap = std::unordered_map<string, MenuBar>;
using CallbackMap = std::unordered_map<CommandID, std::unique_ptr<Callback>>;
using ThreadMap = std::unordered_map<string, std::unique_ptr<Thread>>;
using LayoutMap = std::unordered_map<string, gui::Layout>;

}  // namespace program
}  // namespace rec
