#ifndef __REC_WIDGET_TREE_DIRECTORY__
#define __REC_WIDGET_TREE_DIRECTORY__

#include <algorithm>

#include "rec/widget/tree/Node.h"

namespace rec {
namespace widget {
namespace tree {

class Directory : public Node {
 public:
  typedef juce::Array<File> FileArray;

  Directory(const NodeDesc& d, const ShadowFile s, bool startThread = true);
  ~Directory();

  void computeChildren();

  virtual bool mightContainSubItems() { return true; }
  virtual String name() const;

  virtual void itemClicked(const juce::MouseEvent&) { setOpen(!isOpen()); }
  virtual void itemDoubleClicked(const juce::MouseEvent& m) { itemClicked(m); }

  virtual void itemOpennessChanged (bool isNowOpen);

 private:
  Directory(const Directory& d, const Range& r, bool startThread = true);

  void startThread();

  Range range_;
  FileArray *children_;
  scoped_ptr<Thread> thread_;
  scoped_ptr<FileArray> childrenDeleter_;
  CriticalSection lock_;
  const bool isShard_;
  bool computing_;

  int getLetter(int child, int depth = 1);

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Directory);
};

}  // namespace tree
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_TREE_DIRECTORY__
