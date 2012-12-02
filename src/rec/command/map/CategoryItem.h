#ifndef __REC_COMMAND_COMMANDMAPCATEGORYITEM__
#define __REC_COMMAND_COMMANDMAPCATEGORYITEM__

#include "rec/base/base.h"

namespace rec {
namespace command {

class Editor;

class CategoryItem  : public TreeViewItem {
 public:
  CategoryItem(Editor*, const String& name);

  virtual String getUniqueName() const { return categoryName_ + "_cat"; }
  virtual bool mightContainSubItems() { return true; }
  virtual int getItemHeight() const { return CATEGORY_HEIGHT; }

  virtual void paintItem(Graphics& g, int width, int height);
  virtual void itemOpennessChanged(bool isNowOpen);

  static const int CATEGORY_HEIGHT = 28;

 private:
  Editor* editor_;
  String categoryName_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(CategoryItem);
};


}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMANDMAPCATEGORYITEM__
