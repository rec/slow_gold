#ifndef __REC_WIDGET_TREE_DIRECTORY__
#define __REC_WIDGET_TREE_DIRECTORY__

#include <algorithm>

#include "rec/widget/tree/NodeItem.h"

namespace rec {
namespace widget {
namespace tree {

class Directory : public Node {
 public:
  typedef juce::Array<File> FileArray;

  Directory(const NodeDesc& d, const VolumeFile& vf);
  ~Directory();

  bool computeChildren();
  void partition();
  virtual void addSubItems();
  virtual String name() const;

  virtual void itemClicked(const juce::MouseEvent&) { setOpen(!isOpen()); }
  virtual void itemDoubleClicked(const juce::MouseEvent& m) { itemClicked(m); }

  virtual void itemOpennessChanged (bool isNowOpen);
  virtual void requestPartition();
  virtual bool isDirectory() const { return true; }
  void addChildFile(int b, int e) { addChildFile(createChildFile(b, e)); }

 private:
  typedef std::set<Node*> NodeSet;

  Directory(const Directory& d, const Range& r);

  Node* createChildFile(int begin, int end);
  void addChildFile(Node* node);
  void computeCDChildren();
  void computeFileChildren();

  void resetChildren() {
    childrenDeleter_.reset(new FileArray);
    children_ = childrenDeleter_.get();
  }

  Range range_;
  FileArray *children_;
  scoped_ptr<FileArray> childrenDeleter_;
  scoped_ptr<Thread> thread_;
  CriticalSection lock_;
  NodeSet nodesToAdd_;
  const bool isShard_;
  bool computing_;
  bool computingDone_;
  bool isOpen_;
  mutable String name_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Directory);
  JUCE_LEAK_DETECTOR(Directory);
};

}  // namespace tree
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_TREE_DIRECTORY__
