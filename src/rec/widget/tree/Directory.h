#ifndef __REC_WIDGET_TREE_DIRECTORY__
#define __REC_WIDGET_TREE_DIRECTORY__

#include <algorithm>

#include "rec/widget/tree/NodeItem.h"
#include "rec/util/Range.h"
#include "rec/util/thread/Trash.h"
#include "rec/util/partition/Partition.h"

namespace rec {
namespace widget {
namespace tree {

class Directory : public Node, public Listener<const VirtualFile&> {
 public:
  typedef juce::Array<File> FileArray;

  Directory(const NodeDesc& d, const VirtualFile& vf);
  virtual ~Directory() {}

  virtual void computeChildren();
  virtual void partition();

  virtual void itemClicked() {
    setOpen(!isOpen());
  }

  virtual void itemOpennessChanged(bool isNowOpen);
  virtual void requestPartition();
  virtual bool isDirectory() const { return true; }

  virtual int minPartition() const { return 24; }
  virtual void operator()(const VirtualFile& file) { broadcast(file); }

 protected:
  void addChildFile(Node* node);
  void resetChildren();
  static String getPrefix(const File& f, int letters);

  FileArray *children_;
  Range<int> range_;

 private:
  typedef std::set<Node*> NodeSet;

  Node* createChildFile(const partition::Shard& shard) const;

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
