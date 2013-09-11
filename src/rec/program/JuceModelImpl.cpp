#include "rec/program/JuceModelImpl.h"

#include "rec/command/Command.pb.h"
#include "rec/data/Address.h"
#include "rec/data/Data.h"
#include "rec/data/DataOps.h"
#include "rec/data/proto/FieldOps.h"
#include "rec/program/JuceModel.h"
#include "rec/program/MakeMaps.h"
#include "rec/program/Menu.pb.h"
#include "rec/program/Program.h"

using namespace rec::command;
using namespace rec::data;

TRAN(OPEN_RECENT2, "Open recent");

namespace rec {
namespace program {

namespace {

void checkMenuEntry(const MenuEntry& menuEntry) {
  int cat = 0;
  if (menuEntry.command_size())
    ++cat;
  if (menuEntry.has_submenu())
    ++cat;
  if (menuEntry.is_recent_files_menu())
    ++cat;
  if (menuEntry.has_callout_function())
    ++cat;

  LOG_IF(DFATAL, cat > 1) << "Ambiguous entry: " << menuEntry.DebugString();
}

string getMenuName(const Menu& menu) {
  if (menu.description().menu_size())
    return menu.description().menu(0);

  string menuName = menu.description().name();
  menuName[0] = toupper(menuName[0]);
  return menuName;
}

template <typename PARTS>
bool hasProperty(const Program& program, const PARTS& parts) {
  for (auto& part: parts) {
    if (program.hasProperty(part))
      return true;
  }
  return false;
}

}  // namespace

JuceModelImpl::JuceModelImpl(Program* p, JuceModel* juceModel)
    : program_(p),
      juceModel_(juceModel),
      commandMap_(makeCommandMap(*p)),
      menuMap_(makeMenuMap(*p)),
      menuBarMap_(makeMenuBarMap(*p)) {
  auto commands = program_->commands().command();
  for (auto& cmd: commands) {
    if (cmd.has_setter())
      dataListeners_.push_back(make_unique<SetterListener>(cmd, juceModel));
  }

  program_->registerAllCallbacks();

  for (auto& i: commandMap_)
    program_->getCallback(i.first);

  LOG(INFO) << "There are " << commandMap_.size() << " callback entries!!!!";
}

const MenuBar& JuceModelImpl::menuBar() const {
  return menuBarMap_.at(program_->menuBarName());
}

void JuceModelImpl::addSubMenu(PopupMenu* popup,
                               const MenuEntry& menuEntry) {
  PopupMenu submenu;
  string subname = addMenu(&submenu, menuEntry.submenu());
  popup->addSubMenu(subname, submenu);
}

void JuceModelImpl::addCommand(PopupMenu* popup, CommandID id, bool hasIndex) {
  if (not hasIndex) {
    try {
      const command::Command& command = commandMap_.at(id);
      if (command.index()) {
        PopupMenu submenu;
        for (int i = 0; i < command.index(); ++i)
          addCommand(&submenu, command.command() + i, true);
        popup->addSubMenu(command.submenu_name(), submenu);
        return;
      }
    } catch (const std::out_of_range&) {
      LOG(DFATAL) << "No command for id " << program_->commandName(id);
    }
  }
  popup->addCommandItem(&applicationCommandManager_, id);
}

void JuceModelImpl::addCommands(PopupMenu* popup,
                                  const MenuEntry& menuEntry) {
  for (auto& command: menuEntry.command()) {
    if (command)
      addCommand(popup, command);
    else
      popup->addSeparator();
  }
}

void JuceModelImpl::addMenuEntry(PopupMenu* popup,
                                 const MenuEntry& menuEntry) {
  checkMenuEntry(menuEntry);
  if (menuEntry.command_size())
    addCommands(popup, menuEntry);

  else if (menuEntry.has_submenu())
    addSubMenu(popup, menuEntry);

  else if (menuEntry.is_recent_files_menu())
    makeRecentFiles(popup);

  else if (menuEntry.has_callout_function())
    program_->menuCallout(popup, menuEntry);

  else
    popup->addSeparator();
}

string JuceModelImpl::addMenu(PopupMenu* popup, const string& name) {
  string result;
  try {
    const Menu& menu = menuMap_.at(name);
    for (auto& menuEntry: menu.entry())
      addMenuEntry(popup, menuEntry);

    return getMenuName(menu);
  } catch (const std::out_of_range&) {
    LOG(DFATAL) << "Couldn't get menu " << name;
    return "";
  }
}

void JuceModelImpl::getCommandInfo(CommandID id,
                                   ApplicationCommandInfo* info) {
  try {
    const command::Command& command = commandMap_.at(id);
    const Description& desc = command.desc();

    int flags = command.flags();
    if (hasProperty(*program_, command.disabled()))
      flags |= ApplicationCommandInfo::isDisabled;
    if (hasProperty(*program_, command.ticked()))
      flags |= ApplicationCommandInfo::isTicked;

    static CommandID RECENT_FILES = program_->recentFilesStrategy().
      getRecentFileCommand();
    static CommandID RECENT_FILES_END = RECENT_FILES + command::Command::BANK_SIZE;

    string shortName;
    int nameIndex = id - command.command();
    if (id >= RECENT_FILES && id < RECENT_FILES_END) {
      vector<string> recentFiles = gui::getRecentFileNames();
      int fileIndex = id - RECENT_FILES;
      if (fileIndex >= recentFiles.size())
        shortName = "(missing file)";
      else
        shortName = recentFiles[fileIndex];
    } else if (command.has_setter()) {
      const Setter& setter = command.setter();
      VirtualFile file = setter.is_global() ? global() :
        program_->getCurrentFile();
      Data* data = getData(setter.type_name(), file);
      unique_ptr<Message> msg(data->clone());
      Value value = data::getMessageFieldOrDie(setter.address(), *msg);
      if (setter.type() == Setter::TOGGLE) {
        LOG_IF(DFATAL, not value.has_bool_f()) << "No boolean value.";
        if (value.bool_f())
          flags |= ApplicationCommandInfo::isTicked;
      } else {
        LOG_IF(DFATAL, not value.has_enum_f()) << "No int32 value";
        int32 index = value.enum_f();
        if (index == nameIndex)
          flags |= ApplicationCommandInfo::isTicked;
      }
    }
    if (shortName.empty())
      shortName = desc.menu(nameIndex);

    info->setInfo(shortName, desc.full(0), command.category(), flags);
    if (command.callout())
      program_->commandCallout(command, info);
  } catch (const std::out_of_range&) {
    LOG(DFATAL) << "getCommandInfo out of range " << info->commandID;
  }
}

PopupMenu JuceModelImpl::getMenuForIndex(int menuIndex) {
  PopupMenu menu;
  try {
    const MenuBar& mb = menuBar();
    if (menuIndex >= mb.menu_size())
      LOG(DFATAL) << "out of range: " << menuIndex << " > " << mb.menu_size();
    else
      addMenu(&menu, mb.menu(menuIndex));
  } catch (const std::out_of_range&) {
    LOG(DFATAL) << "Couldn't get menubar " << menuIndex;
  }

  return menu;
}

void JuceModelImpl::makeRecentFiles(PopupMenu* popup) {
  PopupMenu submenu;
  auto& strategy = program_->recentFilesStrategy();
  vector<string> recentFiles = gui::getRecentFileNames(strategy);
  CommandID command = strategy.getRecentFileCommand();
  for (int i = 0; i < recentFiles.size(); ++i)
    addCommand(&submenu, command + i, true);
  popup->addSubMenu(t_OPEN_RECENT2, submenu);
}

bool JuceModelImpl::perform(const InvocationInfo& info) {
  if (Callback* callback = program_->getCallback(info.commandID)) {
    (*callback)();
    return true;
  }
  LOG(DFATAL) << "No command for " << info.commandID;
  return false;
}

StringArray JuceModelImpl::getMenuBarNames() {
  StringArray names;
  try {
    auto menus = menuBar().menu();
    for (auto& name: menus)
      names.add(getMenuName(menuMap_.at(name)));
  } catch (const std::out_of_range&) {
    LOG(DFATAL) << "Couldn't get menu bar";
  }
  return names;
}

}  // namespace program
}  // namespace rec
