#include <stdexcept>

#include "rec/program/JuceModel.h"

#include "rec/gui/menu/RecentFiles.h"
#include "rec/program/JuceModelImpl.h"
#include "rec/program/Menu.pb.h"
#include "rec/program/Program.h"

namespace rec {
namespace program {

static JuceModel* MODEL = nullptr;
JuceModel* juceModel() { return MODEL; }

JuceModel::JuceModel(Program* p) : disableMap_(new DisableMap), program_(p) {
    disableMap_->setProperty("recent_empty", gui::recentFilesEmpty());
}

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

PopupMenu JuceModel::getMenuForIndex(int menuIndex, const String&) {
    return impl_->getMenuForIndex(menuIndex);
}

void JuceModel::invokeAndCheck(CommandID id) {
    if (not invokeDirectly(id, false))
        LOG(DFATAL) << "Failed to invoke " << program_->idToName(id);
}

void JuceModel::operator()(Enable enable) {
    program_->setEnabled(enable);
}

void JuceModel::startThreads() {
    impl_->startThreads();
}

void JuceModel::stopThreads() {
    impl_->stopThreads();
}

Thread* JuceModel::getThread(const string& name) {
    return impl_->getThread(name);
}

const command::CommandMapProto& JuceModel::keyMap() const {
    return impl_->keyMap();
}

const gui::Constants& JuceModel::constants() const {
    return impl_->constants();
}

const gui::Layout& JuceModel::getLayout(const string& name) const {
    return impl_->getLayout(name);
}

bool JuceModel::setProperty(const string& name, bool value) {
    bool result = DisableMap::setProperty(name, value);
    if (result)
        reportChanges();
    return result;
}


}  // namespace program
}  // namespace rec
