#ifndef __REC_APP_PROGRAM__
#define __REC_APP_PROGRAM__

#include "rec/command/Command.pb.h"
#include "rec/command/map/CommandMap.pb.h"
#include "rec/gui/menu/RecentFiles.h"
#include "rec/gui/proto/Layout.pb.h"
#include "rec/gui/proto/Component.pb.h"
#include "rec/program/Menu.pb.h"
#include "rec/program/Threads.pb.h"
#include "rec/program/Types.h"
#include "rec/util/thread/Callback.h"
#include "rec/command/CallbackTable.h"

namespace rec {
namespace program {

typedef int32 (*ThreadFunction)(Thread*);

class Program : public command::CallbackTable{
 public:
  Program() {}
  virtual ~Program() {}

  virtual command::Commands commands() const = 0;
  virtual command::KeyStrokeCommandMapProto keypresses() const = 0;
  virtual Menus menus() const = 0;
  virtual MenuCollection menuCollection() const = 0;
  virtual ThreadProtos threads() const = 0;
  virtual gui::Layouts layouts() const = 0;
  virtual gui::ComponentProtos components() const = 0;

  virtual string menuBarName() const = 0;

  virtual bool hasProperty(const string& name) const = 0;
  virtual void commandCallout(const command::Command&, ApplicationCommandInfo*)
    const = 0;

  // Add an entry only for MenuEntries which have a callout_function.
  virtual void menuCallout(PopupMenu*, const MenuEntry&) const = 0;

  virtual const gui::RecentFilesStrategy& recentFilesStrategy() const = 0;

  // Called before a new command goes off (perhaps to get rid of the "About
  // This Program" window).
  virtual void beforeCommand(CommandID id) = 0;

  virtual void registerAllCallbacks() = 0;
  virtual void addCallback(CommandID, unique_ptr<Callback>) = 0;
  virtual Callback* getCallback(CommandID) const = 0;
  virtual VirtualFile getCurrentFile() const = 0;
  virtual CallbackMap* getCallbackMap() = 0;
  virtual string commandName(CommandID) const = 0;
  virtual bool isEnabled() const = 0;
  virtual void setEnabled(bool) = 0;
  virtual ThreadFunction threadFunction(const string&) const = 0;
};

void registerProgram(Program*);
Program* getProgram();

}  // namespace program
}  // namespace rec

#endif  // __REC_APP_PROGRAM__
