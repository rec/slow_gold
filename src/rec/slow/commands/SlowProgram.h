#pragma once

#include "rec/program/ProgramBase.h"
#include "rec/gui/menu/RecentFiles.h"

namespace rec {
namespace slow {

class Instance;

class SlowProgram : public program::ProgramBase {
  public:
    explicit SlowProgram(Instance*);

    string menuBarName() const override;

    void commandCallout(const command::Command&, ApplicationCommandInfo*)
        const override;

    // Add an entry only for MenuEntries which have a callout_function.
    void menuCallout(PopupMenu*, const program::MenuEntry&) const override {}

    const gui::RecentFilesStrategy& recentFilesStrategy() const override;

    VirtualFile getCurrentFile() const override;
    void beforeCommand(CommandID id) override;

    void registerAllCallbacks() override;
    void registerCustomComponents(gui::Constants*) const override;
    string idToName(CommandID) const override;
    CommandID nameToId(const string&) const override;
    const data::Address& resizerAddress() const override;
    Component* getTopComponent() override;
    string mapTypeName(const string&) const override;
    const char* getPublisherId() const override;
    const char* getActivationId() const override;
    int demoExpirationDays() const override { return EXPIRATION_DAYS; }
    int unauthorizedExpirationDays() const override {
        return UNAUTHORIZED_EXPIRATION_DAYS;
    }

  private:
    Instance* const instance_;
    static const int EXPIRATION_DAYS = 31;
    static const int UNAUTHORIZED_EXPIRATION_DAYS = 2;

    DISALLOW_COPY_ASSIGN_AND_LEAKS(SlowProgram);
};

string mapTypeName(const string&);

}  // namespace slow
}  // namespace rec
