#ifndef __REC_COMPONENT_CONTAINER
#define __REC_COMPONENT_CONTAINER

#include "rec/base/base.h"

using namespace juce;

namespace rec {
namespace slow {

class ComponentContainer : public Component,
                           public MenuBarModel,
                           public ApplicationCommandTarget {

 public:
  ComponentContainer(Component* c) : component_(c) { addAndMakeVisible(c); }

  virtual ~ComponentContainer() {}

  virtual void resized() {
    component_->setBounds(0, 0, getWidth(), getHeight());
  }

  // MenuBarModel virtual methods.
  virtual const StringArray getMenuBarNames() {
    static tchar* const names[] = {NULL};
    return StringArray((const tchar**)names);
  }

  virtual const PopupMenu getMenuForIndex(int menuIndex, const String& menuName) {
    return PopupMenu();
  }

  // ApplicationCommandTarget virtual methods.
  virtual void menuItemSelected(int menuItemID, int topLevelMenuIndex) {}
  virtual void getAllCommands(Array <CommandID>& commands) {}
  virtual void getCommandInfo(CommandID commandID, ApplicationCommandInfo& result) {}
  virtual bool perform(const InvocationInfo& info) { return false; }

  virtual ApplicationCommandTarget* getNextCommandTarget() {
    return findFirstTargetParentComponent();
  }

 protected:
  scoped_ptr<Component> component_;
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_COMPONENT_CONTAINER
