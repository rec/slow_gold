#ifndef __REC_COMMAND_COMMANDMAPCATEGORYITEM__
#define __REC_COMMAND_COMMANDMAPCATEGORYITEM__

#include "rec/command/map/CommandMapItemComponent.h"
#include "rec/command/map/CommandMapEditor.h"

namespace rec {
namespace command {

class CommandMapEditorMappingItem;

class CommandMapCategoryItem  : public TreeViewItem {
 public:
  CommandMapCategoryItem(CommandMapEditor& owner, const String& name);
  virtual CommandMapEditorMappingItem* createItemComponent(CommandID cmd) const;

  virtual String getUniqueName() const { return categoryName_ + "_cat"; }
  virtual bool mightContainSubItems() { return true; }
  virtual int getItemHeight() const { return CATEGORY_HEIGHT; }

  virtual void paintItem(Graphics& g, int width, int height);
  virtual void itemOpennessChanged(bool isNowOpen);

  static const int CATEGORY_HEIGHT = 28;

 private:
  CommandMapEditor& owner_;
  String categoryName_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(CommandMapCategoryItem);
};


}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMANDMAPCATEGORYITEM__
