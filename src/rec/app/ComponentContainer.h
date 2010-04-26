#ifndef __REC_COMPONENT_CONTAINER
#define __REC_COMPONENT_CONTAINER

#include "JuceLibraryCode/JuceHeader.h"

namespace rec {

template <typename WindowType>
class ComponentContainer
  : public Component,
    public MenuBarModel,
    public ApplicationCommandTarget {

 protected:
  WindowType* _window;
  Component* _component;

 public:
  ComponentContainer(WindowType* window) : _window(window), _component(NULL) {}

  void show(Component* component) {
    if (_component) {
      removeChildComponent(_component);
      delete _component;
    }

    _component = component;
    if (_component) {
      addAndMakeVisible(_component);
      resized();
    }
  };

  virtual ~ComponentContainer() {
    deleteAllChildren();
  }

  virtual void resized() {
    if (_component)
      _component->setBounds(0, 0, getWidth(), getHeight());
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
  virtual void getCommandInfo(const CommandID commandID, ApplicationCommandInfo& result) {}
  virtual bool perform(const InvocationInfo& info) { return false; }

  virtual ApplicationCommandTarget* getNextCommandTarget() {
    return findFirstTargetParentComponent();
  }
};

}  // namespace rec

#endif  // __REC_COMPONENT_CONTAINER
