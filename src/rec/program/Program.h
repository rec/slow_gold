#pragma once

#include "rec/command/map/CommandMap.pb.h"
#include "rec/program/Threads.pb.h"
#include "rec/program/Types.h"
#include "rec/util/thread/Callback.h"
#include "rec/util/thread/Looper.h"

namespace rec { namespace command { class Command; }}
namespace rec { namespace data { class Address; }}
namespace rec { namespace gui { class Constants; }}
namespace rec { namespace gui { class RecentFilesStrategy; }}

namespace rec {
namespace program {

class MenuEntry;

class Program {
 public:
  Program() {}
  virtual ~Program() {}

  virtual string menuBarName() const = 0;

  virtual void commandCallout(const command::Command&, ApplicationCommandInfo*)
    const = 0;

  // Add an entry only for MenuEntries which have a callout_function.
  virtual void menuCallout(PopupMenu*, const MenuEntry&) const = 0;

  virtual const gui::RecentFilesStrategy& recentFilesStrategy() const = 0;

  // Called before a new command goes off (perhaps to get rid of the "About
  // This Program" window).
  virtual void beforeCommand(CommandID id) = 0;

  virtual void registerAllCallbacks() = 0;
  virtual void registerCustomComponents(gui::Constants*) const = 0;
  virtual void addCallback(CommandID, unique_ptr<Callback>) = 0;
  virtual Callback* getCallback(CommandID) const = 0;
  virtual VirtualFile getCurrentFile() const = 0;
  virtual CallbackMap* getCallbackMap() = 0;
  virtual string idToName(CommandID) const = 0;
  virtual CommandID nameToId(const string&) const = 0;
  virtual string mapTypeName(const string&) const = 0;
  virtual const char* getPublisherId() const = 0;
  virtual const char* getActivationId() const = 0;
  virtual int demoExpirationDays() const = 0;
  virtual int unauthorizedExpirationDays() const = 0;
  virtual bool isEnabled() const = 0;
  virtual void setEnabled(bool) = 0;
  virtual thread::Looper::Function threadFunction(const string&) const = 0;
  virtual const data::Address& resizerAddress() const = 0;
  virtual Component* getTopComponent() = 0;
};

void registerProgram(Program*);
Program* getProgram();

}  // namespace program
}  // namespace rec

