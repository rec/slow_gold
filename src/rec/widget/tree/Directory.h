#pragma once

#include <algorithm>

#include "rec/widget/tree/NodeItem.h"
#include "rec/util/range/Range.h"
#include "rec/util/thread/Trash.h"
#include "rec/util/partition/Partition.h"

namespace rec {
namespace widget {
namespace tree {

// Skin

class Directory : public Node, public Listener<const VirtualFile&> {
  public:
    typedef juce::Array<File> FileArray;

    Directory(const NodeDesc& d, const VirtualFile& vf);
    virtual ~Directory() {}

    virtual void computeChildren();
    virtual void partition();

    virtual void itemOpennessChanged(bool isNowOpen);
    virtual void requestChildren();
    virtual bool isDirectory() const { return true; }

    virtual int minPartition() const { return 64; }
    virtual void operator()(const VirtualFile& file) { broadcast(file); }
    static bool computeChildrenInBackground();

  protected:
    void addChildFile(Node* node);
    void resetChildren();
    static String getPrefix(const File& f, int letters);

    FileArray *children_;
    Range<int> range_;

  private:
    typedef std::set<Node*> NodeSet;

    Node* createChildFile(const partition::Shard& shard) const;

    std::unique_ptr<FileArray> childrenDeleter_;
    CriticalSection lock_;
    bool isOpen_;
    bool childrenRequested_;
    bool childrenStarted_;
    static NodeSet processingChildren_;
    static CriticalSection processingLock_;

  private:
    DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(Directory);
};

}  // namespace tree
}  // namespace widget
}  // namespace rec
