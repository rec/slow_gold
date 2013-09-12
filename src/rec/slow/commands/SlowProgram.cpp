#include "rec/slow/commands/SlowProgram.h"

#include "rec/command/CommandRecord.h"
#include "rec/command/CommandRecordTable.h"
#include "rec/data/Data.h"
#include "rec/music/Metadata.h"
#include "rec/slow/GuiSettings.pb.h"
#include "rec/slow/Instance.h"
#include "rec/slow/callbacks/Callbacks.h"
#include "rec/slow/commands/SlowCommand.pb.h"
#include "rec/slow/commands/SlowCommandData.h"
#include "rec/translation/TranslationTables.h"
#include "rec/util/Binary.h"
#include "rec/util/LoopPoint.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/widget/waveform/Viewport.pb.h"

using namespace rec::widget::waveform;

TRAN(LOOP_ENTIRE_TRACK, "Loop Entire Track");
TRAN(LOOP_THIS_SEGMENT, "Loop This Segment");

namespace rec {
namespace slow {

namespace {
class SlowRecentFilesStrategy : public gui::RecentFilesStrategy {
 public:
  SlowRecentFilesStrategy() {}

  string getTitle(const gui::RecentFile& rf) const override {
    return music::getTitle(rf.metadata(), rf.file());
  }

  string getDupeSuffix(const gui::RecentFile& rf, bool isFirst) const override {
    const music::Metadata& md = rf.metadata();
    string add = isFirst ? md.album_title() : md.artist();
    if (add.size())
      add += ("(" + add + ")");
    return add;
  }

  CommandID getRecentFileCommand() const override {
    return slow::SlowCommand::RECENT_FILES;
  }
};

static SlowRecentFilesStrategy RECENT_FILES_STRATEGY;

}

command::Commands SlowProgram::commands() const {
  return makeCommand();
}

command::KeyStrokeCommandMapProto SlowProgram::keypresses() const {
  return makeKeyBindings();
}

program::Menus SlowProgram::menus() const {
  SlowMenus slowMenus = BINARY_PROTO(SlowMenus, SlowMenus);
  program::Menus menus;
  for (auto& slowMenu: slowMenus.menu()) {
    program::Menu* menu = menus.add_menu();
    menu->mutable_description()->CopyFrom(slowMenu.description());
    if (slowMenu.has_extends())
      menu->set_extends(slowMenu.extends());
    for (auto& slowEntry: slowMenu.entry()) {
      program::MenuEntry* menuEntry = menu->add_entry();
      for (auto& command: slowEntry.command())
        menuEntry->add_command(command);
      if (slowEntry.has_submenu())
        menuEntry->set_submenu(slowEntry.submenu());
      if (slowEntry.has_callout_function())
        menuEntry->set_callout_function(slowEntry.callout_function());
    }
  }

  return menus;
}

program::MenuCollection SlowProgram::menuCollection() const {
  return BINARY_PROTO(SlowMenuCollection, program::MenuCollection);
}

string SlowProgram::menuBarName() const {
  return data::getProto<GuiSettings>().advanced_menus() ? "advanced" : "basic";
}

bool SlowProgram::hasProperty(const string& name) const {
  if (name == "empty")
    return instance_->empty();

  if (name == "one_or_fewer_segments") {
    return ProgramBase::hasProperty("empty") or
      (data::getProto<Viewport>(instance_->file()).loop_points().
       loop_point_size() <= 1);
  }

  return ProgramBase::hasProperty(name);
}

void SlowProgram::commandCallout(const command::Command& command,
                                 ApplicationCommandInfo* info) const {
  DCHECK_EQ(command.command(), SlowCommand::TOGGLE_WHOLE_SONG_LOOP);
  auto lpl = data::getProto<Viewport>(instance_->file()).loop_points();
  if (lpl.loop_point_size() <= 1 or audio::getSelectionCount(lpl) == 1)
    info->shortName = t_LOOP_ENTIRE_TRACK;
  else
    info->shortName = t_LOOP_THIS_SEGMENT;
}

const gui::RecentFilesStrategy& SlowProgram::recentFilesStrategy() const {
  return RECENT_FILES_STRATEGY;
}

void SlowProgram::registerAllCallbacks() {
  slow::addSlowCallbacks(this);
}

VirtualFile SlowProgram::getCurrentFile() const {
  return instance_->file();
}

void SlowProgram::beforeCommand(CommandID id) {
	if (id != SlowCommand::ABOUT_THIS_PROGRAM && instance_->window_)
    thread::callAsync(instance_->window_, &app::Window::stopAboutWindow);
}

const int MARGIN = 10;

string SlowProgram::commandName(CommandID id) const {
  return rec::slow::commandName(id);
}

string commandName(CommandID id) {
  bool isCompound = id > command::Command::BANK_SIZE - MARGIN;
  int mod;
  if (isCompound) {
    mod = (id + MARGIN) % command::Command::BANK_SIZE - MARGIN;
    id -= mod;
  }
  string name = SlowCommand_Type_Name(static_cast<SlowCommand::Type>(id));
  if (isCompound)
    name += str(":" + String(mod));
  return name;
}

}  // namespace slow
}  // namespace rec
