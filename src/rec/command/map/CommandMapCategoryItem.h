#ifndef __REC_COMMAND_COMMANDMAPCATEGORYITEM__
#define __REC_COMMAND_COMMANDMAPCATEGORYITEM__

#include "rec/command/map/CommandMapItemComponent.h"
#include "rec/command/map/CommandMapEditor.h"

namespace rec {
namespace command {

class CommandMapEditorMappingItem;

//==============================================================================
class CommandMapCategoryItem  : public TreeViewItem
{
 public:
  CommandMapCategoryItem (CommandMapEditor& owner, const String& name);
  virtual CommandMapEditorMappingItem* createItemComponent(CommandID cmd) const;

  virtual String getUniqueName() const { return categoryName + "_cat"; }
  virtual bool mightContainSubItems() { return true; }
  virtual int getItemHeight() const { return 28; }

  virtual void paintItem(Graphics& g, int width, int height);
  virtual void itemOpennessChanged(bool isNowOpen);

 private:
  CommandMapEditor& owner;
  String categoryName;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CommandMapCategoryItem);
};


}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMANDMAPCATEGORYITEM__
