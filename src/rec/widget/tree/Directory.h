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

  virtual String name() const;

  virtual void itemClicked(const juce::MouseEvent&) { setOpen(!isOpen()); }
  virtual void itemDoubleClicked(const juce::MouseEvent& m) { itemClicked(m); }

  virtual void itemOpennessChanged (bool isNowOpen);
  virtual void startThread();

 protected:
  virtual bool isDirectory() const { return true; }

 private:
  Directory(const Directory& d, const Range& r, bool startThread = true);

  ShadowFile getChildShadowFile(int child);
  int getLetter(int child, int depth = 1);

  Range range_;
  FileArray *children_;
  scoped_ptr<FileArray> childrenDeleter_;
  scoped_ptr<Thread> thread_;
  CriticalSection lock_;
  const bool isShard_;
  bool computing_;
  bool computingDone_;
  bool isOpen_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Directory);
};

}  // namespace tree
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_TREE_DIRECTORY__
