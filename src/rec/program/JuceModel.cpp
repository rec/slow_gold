#include <stdexcept>

#include "rec/program/JuceModel.h"

#include "rec/program/JuceModelImpl.h"
#include "rec/program/Menu.pb.h"
#include "rec/program/Program.h"

namespace rec {
namespace program {

static JuceModel* MODEL = nullptr;
JuceModel* juceModel() { return MODEL; }
JuceModel::JuceModel(Program* p) : program_(p) {}

void JuceModel::init() {
  impl_.reset(new JuceModelImpl(program_, this));
  CHECK(not MODEL);
  MODEL = this;
}

JuceModel::~JuceModel() {
  CHECK(MODEL == this);
  MODEL = nullptr;
}

void JuceModel::getAllCommands(juce::Array<CommandID>& commands) {
  for (auto& mapEntry: impl_->commandMap())
    commands.add(mapEntry.first);
}

void JuceModel::getCommandInfo(CommandID id,
                               ApplicationCommandInfo& info) {
  impl_->getCommandInfo(id, &info);
}

bool JuceModel::perform(const InvocationInfo& info) {
  return impl_->perform(info);
}

StringArray JuceModel::getMenuBarNames() {
  return impl_->getMenuBarNames();
}

ApplicationCommandManager* JuceModel::applicationCommandManager() {
  return impl_->applicationCommandManager();
}

PopupMenu JuceModel::getMenuForIndex(int menuIndex, const String&) {
  return impl_->getMenuForIndex(menuIndex);
}

void JuceModel::operator()(command::ID id) {
  (*this)(id.get());
}

void JuceModel::operator()(CommandID id) {
  if (not applicationCommandManager()->invokeDirectly(id, false))
    LOG(DFATAL) << "Failed to invoke " << program_->commandName(id);
}

void JuceModel::operator()(Enable enable) {
  program_->setEnabled(enable);
}

}  // namespace program
}  // namespace rec
