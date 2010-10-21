#include <glog/logging.h>
#include "rec/widget/tree/Directory.h"
#include "rec/widget/tree/SortedChildren.h"
#include "rec/util/Utf8.h"

namespace rec {
namespace widget {
namespace tree {

namespace {

class Shard : public Directory {
 public:
  Shard(const Directory& d, const String& p, const Range& r, const Range& ltr)
      : Directory(d, r), prefix_(p), letter_(ltr) {
  }

  virtual String name() { return letter_.begin_ + "..." + letter_.end_; }

 private:
  const String prefix_;
  const Range letter_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Shard);
};

}  // namespace

void Directory::fillSubItems() {
  File f = shadow_.file_;
  if (!f.exists()) {
    LOG(ERROR) << f.getFullPathName().toCString() << " doesn't exist";
    return;
  }
  if (!f.isDirectory()) {
    LOG(ERROR) << f.getFullPathName().toCString() << " is not a directory";
    return;
  }

  if (!children_) {
    children_ = new FileArray;
    childrenDeleter_.reset(children_);
    sortedChildren(f, children_);
    range_.begin_ = 0;
    range_.end_ = children_->size();
  }

  if (range_.size() <= desc_.max_branch())
    fillFewItems();
  else
    fillManyItems();
}

void Directory::fillFewItems() {
  for (int i = range_.begin_; i != range_.end_; ++i) {
    const File& f = (*children_)[i];
    ShadowFile sf(f, shadow_.shadow_.getChildFile(f.getFileName()));
    bool isDir = f.isDirectory();
    addSubItem(isDir ? new Directory(desc_, sf) : new Node(desc_, sf));
  }
}

void Directory::fillManyItems() {
  int size = children_->size();
  if (getLetter(0) == getLetter(size - 1)) {
    // Awful special case - all the files in a larger directory start with the
    // same first letter.  But this can happen and we can't afford to get into
    // an infinite loop in this case!
    return;  // TODO
  }

  int branch = desc_.best_branch();
  for (int child = 0, i = 0; child < size; ++i) {
    int remaining = size - child;
    int slots = branch - i;
    int slotSize = (remaining + slots / 2) / slots;
    if (slotSize < 1)
      slotSize = 1;

    int t = child + slotSize;
    if (t > size)
      t = size;

    // Include everything with the same first letter.
    int nextLetter = getLetter(t - 1);
    for (; t < size && getLetter(t) == nextLetter; ++t);
    int letter = getLetter(child);
    addSubItem(new Shard(*this, "", Range(child, t),
                         Range(letter, nextLetter)));
    child = t;
  }
}

int Directory::getLetter(int child, int depth) {
  StringPiece s((*children_)[child].getFileName().toCString(), s.size());

  int letter;
  for (; depth; depth--) {
    const char* error;
    letter = util::utf8::decode(&s, &error);
    CHECK(NULL == error) << "UTF-8 error " << error;
  }
  return letter;
}

}  // namespace tree
}  // namespace widget
}  // namespace rec
