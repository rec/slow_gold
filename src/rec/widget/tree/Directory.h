#ifndef __REC_WIDGET_TREE_DIRECTORY__
#define __REC_WIDGET_TREE_DIRECTORY__

#include <algorithm>

#include "rec/widget/tree/NodeItem.h"
#include "rec/util/Range.h"
#include "rec/util/thread/Trash.h"

namespace rec {
namespace widget {
namespace tree {

class Directory : public Node {
 public:
  typedef juce::Array<File> FileArray;

  Directory(const NodeDesc& d, const VolumeFile& vf);
  virtual ~Directory() {}

  virtual void computeChildren();
  virtual void partition();

  void addNode(Node* node);

  virtual void itemClicked(const juce::MouseEvent&) { setOpen(!isOpen()); }
  virtual void itemDoubleClicked(const juce::MouseEvent& m) { itemClicked(m); }

  virtual void itemOpennessChanged(bool isNowOpen);
  virtual void requestPartition();
  virtual bool isDirectory() const { return true; }
  void addChildFile(int b, int e) { addChildFile(createChildFile(b, e)); }
  virtual int minPartition() const { return 12; }

 protected:
  void addChildFile(Node* node);
  void resetChildren();
  static String getSub(const File& f, int letters);

  FileArray *children_;
  Range<int> range_;

 private:
  typedef std::set<Node*> NodeSet;

  virtual Node* createChildFile(int begin, int end) const;

  thread_ptr<Thread> thread_;
  ptr<FileArray> childrenDeleter_;
  CriticalSection lock_;
  bool isOpen_;

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(Directory);
  JUCE_LEAK_DETECTOR(Directory);
};

}  // namespace tree
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_TREE_DIRECTORY__
