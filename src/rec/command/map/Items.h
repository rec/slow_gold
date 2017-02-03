#pragma once

#include "rec/base/base.h"

namespace rec {
namespace command {

class EditButton;
class Editor;

class Item : public juce::TreeViewItem {
 public:
  Item(const String& name, const String& suffix, bool hasSubItems)
      : name_(name), suffix_(suffix), hasSubItems_(hasSubItems) {}
  virtual bool mightContainSubItems() { return hasSubItems_; }
  virtual String getUniqueName() const { return name_ + suffix_; }

 protected:
  const String name_;
  const String suffix_;
  const bool hasSubItems_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(Item);
};

class CategoryItem : public Item {
 public:
  CategoryItem(const String& name, Component*);
  virtual int getItemHeight() const { return HEIGHT; }
  virtual void paintItem(Graphics& g, int width, int height);

 private:
  static const int HEIGHT = 28;
  Component* const component_;
  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(CategoryItem);
};

class MapItem : public Item {
 public:
  MapItem(Editor*, CommandID, const String& name);
  int getItemHeight() const { return HEIGHT; }

  Component* createItemComponent();

 private:
  static const int HEIGHT = 20;
  Editor* const editor_;
  const CommandID id_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(MapItem);
};

class MapItemComponent  : public Component {
 public:
  MapItemComponent(Editor* editor, CommandID, const String& name);
  ~MapItemComponent();
  void createEditButton(const String& desc, int index, bool isReadOnly);
  void paint(Graphics&);
  void resized();

  const CommandID commandID_;

 private:
  String name_;
  Editor* editor_;
  juce::OwnedArray<EditButton> buttons_;
};

}  // namespace command
}  // namespace rec

