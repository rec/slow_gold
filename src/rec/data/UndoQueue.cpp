#include "rec/data/UndoQueue.h"

#include "rec/data/Action.pb.h"
#include "rec/data/Editable.h"
#include "rec/data/Grouper.h"
#include "rec/data/Value.h"
#include "rec/data/proto/Equals.h"
#include "rec/util/Math.h"
#include "rec/util/STL.h"
#include "rec/util/file/LogFile.h"

namespace rec {
namespace data {

class UndoEntry {
 public:
  static const uint64 MAX_GROUP_TIME = 2000;
  static const bool GROUP_BY_TIME = true;

  UndoEntry(Editable* e, const Message& b, const Message& a, int64 t = 0)
      : editable_(e), before_(clone(b)), after_(clone(a)), timestamp_(t) {
    if (!timestamp_)
      timestamp_ = juce::Time::currentTimeMillis();
  }

  bool mergeInto(UndoEntry* ue) {
    if (ue->editable_ != editable_ ||
        GROUP_BY_TIME && !near(ue->timestamp(), timestamp(), MAX_GROUP_TIME))
      return false;

    after_.swap(ue->after_);
    return true;
  }

  void setDataValue(bool isBefore) {
    editable_->setDataValue(isBefore ? *before_ : *after_);
    editable_->updateClients();
    editable_->needsUpdate();
  }

  Editable* editable_;
  ptr<Message> before_;
  ptr<Message> after_;
  int64 timestamp_;
};

static void addInto(UndoQueue::Queue* q, UndoEntry* ue, bool canMerge) {
  if (canMerge && q->size() && q->back()->mergeInto(ue))
    delete ue;
  else
    q->push_back(ue);
}


UndoQueue::~UndoQueue() {
  Lock l(lock_);
  stl::deletePointers(&queue_);
}

bool UndoQueue::discardRedos() {
  if (!undoes_)
    return false;

  uint newSize = queue_.size() - undoes_;
  for (uint i = newSize; i < queue_.size(); ++i)
    delete queue_[i];

  queue_.resize(newSize);
  undoes_ = 0;
}

void UndoQueue::addToQueue(Editable* e, const Message& before,
                           const Message& after) {
  {
    Lock l(lock_);
    if (!(running_ && operations.undoable()))
      return;
    bool canMerge = !discardRedos();
    addInto(&queue_, new UndoEntry(e, before, after), canMerge);
  }
  broadcast(None());
}

void UndoQueue::redoOrUndo(bool isUndo) {
  int pos = queue_.size() - (isUndo ? undoes_-- : ++undoes_);
  queue_[pos]->setDataValue(isUndo);

  broadcast(None());
}

void UndoQueue::undo() {
  if (undoable())
    redoOrUndo(true);
  else
    LOG(DFATAL) << "Tried to undo when nothing was undoable";
}

void UndoQueue::redo() {
  if (undoes())
    redoOrUndo(false);
  else
    LOG(DFATAL) << "Tried to redo when nothing was redoable";
}

void UndoQueue::start() {
  running_ = true;
}

void UndoQueue::stop() {
  running_ = false;
}

void UndoQueue::dump(const string& name) const {
  DLOG(INFO) << name;
  for (uint i = 0; i < queue_.size(); ++i) {
    bool isCurrent = (i == (queue_.size() - undoes_ - 1));
    std::cerr << (isCurrent ? " --> " : "     ")
              << queue_[i]->ShortDebugString()
              << "\n";
  }
}

}  // namespace data
}  // namespace rec
