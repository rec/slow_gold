#ifndef __REC_COMPONENT_CONTAINER
#define __REC_COMPONENT_CONTAINER

#include "rec/base/base.h"

#include "JuceLibraryCode/JuceHeader.h"

namespace rec {

class ComponentContainer
  : public Component,
    public MenuBarModel,
    public ApplicationCommandTarget {

 protected:
  Component* component_;

 public:
  ComponentContainer() : component_(NULL) {}

  void show(Component* component) {
    if (component_) {
      removeChildComponent(component_);
      delete component_;
    }

    component_ = component;
    if (component_) {
      addAndMakeVisible(component_);
      resized();
    }
  };

  virtual ~ComponentContainer() {
    deleteAllChildren();
  }

  virtual void resized() {
    if (component_)
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

  juce_UseDebuggingNewOperator
};

}  // namespace rec

#endif  // __REC_COMPONENT_CONTAINER
