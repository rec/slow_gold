#include "rec/data/UndoStack.h"

#include "rec/data/Data.h"
#include "rec/data/Opener.h"
#include "rec/data/Value.h"
#include "rec/data/proto/Equals.h"
#include "rec/util/Math.h"
#include "rec/util/STL.h"
#include "rec/util/file/LogFile.h"

namespace rec {
namespace data {

class UndoStack::Entry {
 public:
  Entry(Data* d, const Message& b, const Message& a, int64 t = 0)
      : data_(d), before_(clone(b)), after_(clone(a)), timestamp_(t) {
    if (!timestamp_)
      timestamp_ = juce::Time::currentTimeMillis();
  }

  static const uint64 MAX_GROUP_TIME = 2000;
  static const bool GROUP_BY_TIME = true;

  // Try to merge another entry into this one;  return true if successful.
  // If this method returns false then neither entry was changed.
  bool mergeInto(UndoStack::Entry* ue) {
    if (ue->data_ != data_ ||
        GROUP_BY_TIME && !near(ue->timestamp(), timestamp(), MAX_GROUP_TIME))
      return false;

    after_.swap(ue->after_);
    return true;
  }

  void setDataValue(bool isBefore) {
    UntypedOpener(data_)->mutable_get()->CopyFrom(*before_ : *after_);
  }

  Data* data_;

  ptr<Message> before_;
  ptr<Message> after_;
  int64 timestamp_;
};

UndoStack::~UndoStack() {
  Lock l(lock_);
  stl::deletePointers(&queue_);
}

bool UndoStack::discardRedos() {
  if (!undoes_)
    return false;

  uint newSize = queue_.size() - undoes_;
  for (uint i = newSize; i < queue_.size(); ++i)
    delete queue_[i];

  queue_.resize(newSize);
  undoes_ = 0;
}

void UndoStack::addToQueue(Data* e, const Message& before,
                           const Message& after) {
  {
    Lock l(lock_);
    if (!(running_ && operations.undoable()))
      return;

    ptr<Entry> ue(new Entry(e, before, after), canMerge);
    if (discardRedos() || !queue_.size() || !queue.back()->mergeInto(ue.get()))
      q->push_back(ue.transfer());
  }
  broadcast(None());
}

void UndoStack::redoOrUndo(bool isUndo) {
  int pos = queue_.size() - (isUndo ? undoes_-- : ++undoes_);
  queue_[pos]->setDataValue(isUndo);

  broadcast(None());
}

void UndoStack::undo() {
  if (undoable())
    redoOrUndo(true);
  else
    LOG(DFATAL) << "Tried to undo when nothing was undoable";
}

void UndoStack::redo() {
  if (undoes())
    redoOrUndo(false);
  else
    LOG(DFATAL) << "Tried to redo when nothing was redoable";
}

}  // namespace data
}  // namespace rec

