#ifndef __REC_COMPONENT_CONTAINER
#define __REC_COMPONENT_CONTAINER

#include "rec/command/Command.h"
#include "rec/slow/MainPage.h"
#include "rec/slow/CommandTarget.h"

using namespace juce;

namespace rec {
namespace slow {

class ComponentContainer : public Component, public MenuBarModel {
 public:
  ComponentContainer();
  virtual ~ComponentContainer();

  virtual void resized();

  void clearTree();
  void clearFile();
  void audioPreferences();

  virtual void menuItemSelected(int menuItemID, int topLevelMenuIndex);
  void doMenuItemSelected(int menuItemID, int topLevelMenuIndex);

  // ApplicationCommandTarget virtual methods.
  virtual void getAllCommands(Array <CommandID>&) {}
  virtual void getCommandInfo(CommandID, ApplicationCommandInfo&) {}
  virtual bool perform(const InvocationInfo&) { return false; }

  virtual ApplicationCommandTarget* getNextCommandTarget();

 private:
  MainPage mainPage_;
  SlowTarget target_;

  DISALLOW_COPY_AND_ASSIGN(ComponentContainer);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_COMPONENT_CONTAINER
