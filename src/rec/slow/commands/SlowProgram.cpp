#include "rec/slow/commands/SlowProgram.h"

#include "rec/audio/source/Player.h"
#include "rec/command/CommandData.h"
#include "rec/data/Data.h"
#include "rec/data/DataCenter.h"
#include "rec/data/DataUpdater.h"
#include "rec/music/Metadata.h"
#include "rec/slow/Components.h"
#include "rec/slow/GuiSettings.pb.h"
#include "rec/slow/Instance.h"
#include "rec/slow/callbacks/Callbacks.h"
#include "rec/slow/commands/Command.pb.h"
#include "rec/translation/TranslationTables.h"
#include "rec/util/BinaryMacros.h"
#include "rec/util/Copy.h"
#include "rec/util/LoopPoint.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/util/thread/Result.h"
#include "rec/widget/tree/Root.h"
#include "rec/widget/waveform/Viewport.pb.h"

using namespace rec::data;
using namespace rec::widget::waveform;
using namespace rec::widget::tree;

TRAN(LOOP_ENTIRE_TRACK, "Loop Entire Track");
TRAN(LOOP_THIS_SEGMENT, "Loop This Segment");

namespace rec {
namespace slow {

namespace {

class SlowRecentFilesStrategy : public gui::RecentFilesStrategy {
 public:
  SlowRecentFilesStrategy() {}

  string getTitle(const gui::RecentFile& rf) const override {
    music::Metadata md;
    copy::copy(rf.metadata_string(), &md);
    return music::getTitle(md, rf.file());
  }

  string getDupeSuffix(const gui::RecentFile& rf, bool isFirst) const override {
    music::Metadata md;
    copy::copy(rf.metadata_string(), &md);
    string add = isFirst ? md.album_title() : md.artist();
    if (add.size())
      add += ("(" + add + ")");
    return add;
  }

  CommandID getRecentFileCommand() const override {
    return slow::Command::RECENT_FILES;
  }
};

static SlowRecentFilesStrategy RECENT_FILES_STRATEGY;

int navigator(Thread*) {
  getInstance()->components_->directoryTree_->checkVolumes();
  return thread::WAIT;
}

int writeGui(Thread* thread) {
  MessageManagerLock l(thread);
  if (!l.lockWasGained())
    return thread::DONE;
  getInstance()->updateGui();
  return thread::WAIT;
}

int writeData(Thread*) {
  data::getDataCenter().updater_->write();
  return thread::WAIT;
}

int updateData(Thread* thread) {
  MessageManagerLock l(thread);
  if (!l.lockWasGained())
    return thread::DONE;
  data::getDataCenter().updater_->update();
  return thread::WAIT;
}

int directory(Thread*) {
  return getInstance()->components_->directoryTree_->run() ? thread::YIELD :
    thread::WAIT;
}

int timer(Thread*) {
  getInstance()->player_->timer()->broadcastTime();
  return thread::WAIT;
}

}  // namespace

SlowProgram::SlowProgram(Instance* instance) : instance_(instance) {
  threadFunctions_["navigator"] = navigator;
  threadFunctions_["writeGui"] = writeGui;
  threadFunctions_["writeData"] = writeData;
  threadFunctions_["updateData"] = updateData;
  threadFunctions_["directory"] = directory;
  threadFunctions_["timer"] = timer;
}

command::Commands SlowProgram::commands() const {
  return command::convertCommands<slow::Commands>();
}

command::KeyStrokeCommandMapProto SlowProgram::keypresses() const {
  return command::convertKeyBindings<slow::CommandMapProto>();
}

program::Menus SlowProgram::menus() const {
  Menus slowMenus = BINARY_PROTO(Menus, Menus);
  program::Menus menus;
  for (auto& slowMenu: slowMenus.menu()) {
    program::Menu* menu = menus.add_menu();
    menu->mutable_description()->CopyFrom(slowMenu.description());
    if (slowMenu.has_extends())
      menu->set_extends(slowMenu.extends());
    for (auto& slowEntry: slowMenu.entry()) {
      program::MenuEntry* menuEntry = menu->add_entry();
      for (auto& id: slowEntry.id())
        menuEntry->add_id(id);
      if (slowEntry.has_submenu())
        menuEntry->set_submenu(slowEntry.submenu());
      if (slowEntry.has_callout_function())
        menuEntry->set_callout_function(slowEntry.callout_function());
    }
  }

  return menus;
}

program::MenuCollection SlowProgram::menuCollection() const {
  return BINARY_PROTO(MenuCollection, program::MenuCollection);
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
  DCHECK_EQ(command.id(), Command::TOGGLE_WHOLE_SONG_LOOP);
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
	if (id != Command::ABOUT_THIS_PROGRAM && instance_->window_)
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
  string name = Command_Id_Name(static_cast<Command::Id>(id));
  if (isCompound)
    name += str(":" + String(mod));
  return name;
}

}  // namespace slow
}  // namespace rec
