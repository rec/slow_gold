#include "rec/program/JuceModelImpl.h"

#include "rec/command/Command.pb.h"
#include "rec/data/Address.h"
#include "rec/data/Data.h"
#include "rec/data/DataOps.h"
#include "rec/data/proto/FieldOps.h"
#include "rec/gui/menu/RecentFiles.h"
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
  if (menuEntry.id_size())
    ++cat;
  if (menuEntry.has_submenu())
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

template <typename Parts>
bool hasProperty(const JuceModel& model, const Parts& parts) {
  for (auto& part: parts) {
    if (model.getProperty(part))
      return true;
  }
  return false;
}

}  // namespace

JuceModelImpl::JuceModelImpl(Program* p, JuceModel* juceModel)
    : program_(p),
      juceModel_(juceModel),
      commandMap_(makeCommandMap(*p)),
      keyMap_(makeKeyMap(*p)),
      menuMap_(makeMenuMap(*p)),
      menuBarMap_(makeMenuBarMap(*p)),
      layoutMap_(makeLayoutMap(*p)),
      threadMap_(makeThreadMap(*p)),
      constants_(makeConstants()),
      recentFiles_(program_->recentFilesStrategy().getRecentFileCommand()),
      recentFilesEnd_(recentFiles_ + command::Command::BANK_SIZE) {
  program_->registerCustomComponents(&constants_);
  mergeKeysIntoCommands(keyMap_, &commandMap_);
  for (auto& i: commandMap_) {
    Command& cmd = i.second;
    if (cmd.has_setter()) {
      dataListeners_.push_back(make_unique<SetterListener>(
          i.first, cmd, juceModel));
    }
  }
  program_->registerAllCallbacks();

  for (auto& i: commandMap_)
    program_->getCallback(i.first);
  logMaps();
}

void JuceModelImpl::logMaps() {
  if (true)
    return;
  LOG(INFO) << "There are " << commandMap_.size() << " callbacks.";
  LOG(INFO) << "There are " << layoutMap_.size() << " layouts.";

  int undeclared = 0, total = 0, empty = 0;
  for (auto& i: layoutMap_) {
    if (not (i.second.has_container() or i.second.component().size())) {
      DLOG(INFO) << "empty: " << i.second.name();
      ++empty;
    }
    for (auto& component: i.second.component()) {
      auto& name = component.name();
      if (not name.empty()) {
        total += 1;
      }
    }
  }
  LOG(INFO) << "There are " << undeclared << " missing components out of "
            << total << " and " << empty << " empty layouts.";

  if (false)
  for (auto& i: layoutMap_)
    LOG(INFO) << i.first << " : " << i.second.ShortDebugString();
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

void JuceModelImpl::addSingleCommand(PopupMenu* popup, CommandID id) {
  popup->addCommandItem(juceModel_->applicationCommandManager(), id);
}

void JuceModelImpl::addCommand(PopupMenu* popup, CommandID id, bool hasIndex) {
  if (isRecentFiles(id)) {
    makeRecentFiles(popup);
    return;
  }
  const command::Command* command;
  try {
    command = &commandMap_.at(id);
  } catch (const std::out_of_range&) {
    LOG(DFATAL) << "No command for id " << program_->idToName(id);
    return;
  }
  if (not command->index()) {
    addSingleCommand(popup, id);
    return;
  }

  auto& seps = command->submenu_separator();
  int nextSep = 0;
  PopupMenu submenu;
  for (int i = 0; i < command->index(); ++i) {
    if (nextSep < seps.size() and i == seps.Get(nextSep)) {
      submenu.addSeparator();
      ++nextSep;
    }
    addSingleCommand(&submenu, command->id() + i);
  }
  popup->addSubMenu(command->submenu_name(), submenu);
}

void JuceModelImpl::addCommands(PopupMenu* popup,
                                  const MenuEntry& menuEntry) {
  for (auto& id: menuEntry.id()) {
    if (id)
      addCommand(popup, id);
    else
      popup->addSeparator();
  }
}

void JuceModelImpl::addMenuEntry(PopupMenu* popup,
                                 const MenuEntry& menuEntry) {
  checkMenuEntry(menuEntry);
  if (menuEntry.id_size())
    addCommands(popup, menuEntry);

  else if (menuEntry.has_submenu())
    addSubMenu(popup, menuEntry);

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
    if (hasProperty(*juceModel_, command.disabled()))
      flags |= ApplicationCommandInfo::isDisabled;
    if (hasProperty(*juceModel_, command.ticked()))
      flags |= ApplicationCommandInfo::isTicked;

    string shortName;
    int nameIndex = id - command.id();
    if (isRecentFiles(id)) {
      vector<string> recentFiles = gui::getRecentFileNames();
      int fileIndex = id - recentFiles_;
      if (fileIndex >= recentFiles.size())
        shortName = "(missing file)";
      else
        shortName = recentFiles[fileIndex];
    } else if (command.has_setter()) {
      data::Address address(command.setter());
      bool isGlobal = (address.getScope() == data::AddressProto::GLOBAL_SCOPE);
      VirtualFile file = isGlobal ? global() : program_->getCurrentFile();
      Data* data = getData(address.type_name(), file);
      unique_ptr<Message> msg(data->clone());
      Value value = data::getMessageFieldOrDie(address, *msg);
      if (command.setter_type() == Command::TOGGLE) {
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
  vector<string> recentFiles = gui::getRecentFileNames();
  const command::Command& command = commandMap_[recentFiles_];
  auto& seps = command.submenu_separator();
  int nextSep = 0;
  for (int i = 0; i < recentFiles.size(); ++i) {
    if (nextSep < seps.size() and i == seps.Get(nextSep)) {
      submenu.addSeparator();
      ++nextSep;
    }
    addSingleCommand(&submenu, recentFiles_ + i);
  }

  popup->addSubMenu(command.submenu_name(), submenu);
}


bool JuceModelImpl::perform(const InvocationInfo& info) {
  auto id = info.commandID;
  if (not (program_->isEnabled() or
           id == juce::StandardApplicationCommandIDs::quit)) {
    return false;
  }

  if (auto callback = program_->getCallback(id)) {
    (*callback)();
    return true;
  }
  LOG(DFATAL) << "No command for " << info.commandID;
  return false;
}

StringArray JuceModelImpl::getMenuBarNames() {
  StringArray names;
  auto bar = menuBar();
  for (auto& name: menuBar().menu()) {
    try {
      names.add(getMenuName(menuMap_.at(name)));
    } catch (const std::out_of_range&) {
      LOG(DFATAL) << "Couldn't get menu " << name
                  << " for menu bar " << bar.description().name();
    }
  }
  return names;
}

bool JuceModelImpl::isRecentFiles(CommandID id) const {
  return id >= recentFiles_ && id < recentFilesEnd_;
}

void JuceModelImpl::startThreads() {
  for (auto& i: threadMap_)
    i.second->startThread();
}

static const int THREAD_STOP_PERIOD = 2500;

void JuceModelImpl::stopThreads() {
  for (auto& i: threadMap_)
    i.second->stopThread(THREAD_STOP_PERIOD);
}

Thread* JuceModelImpl::getThread(const string& name) {
  return threadMap_.at(name).get();
}

Component* JuceModelImpl::getComponent(const string& name) const {
  if (not componentMap_.get()) {
    componentMap_.reset(new gui::ComponentMap(
        gui::getComponentMap(program_->getTopComponent())));
  }
  return componentMap_->at(name);
}

string JuceModelImpl::componentNames() const {
  StringArray names;
  for (auto& i: *componentMap_)
    names.add(str(i.first));
  return str(names.joinIntoString(", "));
}

}  // namespace program
}  // namespace rec
