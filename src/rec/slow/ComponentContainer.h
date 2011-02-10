#ifndef __REC_COMPONENT_CONTAINER
#define __REC_COMPONENT_CONTAINER

#include "rec/base/base.h"

using namespace juce;

namespace rec {
namespace slow {

class MainPageComponent;
class MainPage;

class ComponentContainer : public Component,
                           public MenuBarModel,
                           public ApplicationCommandTarget {
 public:
  ComponentContainer(MainPageComponent* c);
  virtual ~ComponentContainer();

  virtual void resized();
  virtual const StringArray getMenuBarNames();

  enum MenuItems { OPEN = 1, CLOSE, CUT, COPY, PASTE, QUIT, EJECT, CLEAR_TREE,
                   CLEAR_TIME, CLEAR_FILE, AUDIO_PREFERENCES, RECENT_FILES,
                   LAST_MENU_ITEM };

  virtual const PopupMenu getMenuForIndex(int index, const String& name);

  void open();
  void close();
  void cut();
  void copy();
  void paste();
  void quit();
  void eject();
  void clearTree();
  void clearTime();
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
  ptr<MainPageComponent> mainComponent_;

  DISALLOW_COPY_AND_ASSIGN(ComponentContainer);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_COMPONENT_CONTAINER
